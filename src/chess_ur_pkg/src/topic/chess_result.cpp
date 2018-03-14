#include <ros/ros.h>
#include <chess_msgs/Move.h>
#include <chess_msgs/Result.h>
#include <chess_msgs/Operation.h>

class ChessResult
{
    protected:
        ros::NodeHandle nh_;
        ros::Subscriber result_sub_;
        ros::Publisher move_pub_;

    public:
        ChessResult(std::string topic);
        ~ChessResult();

        void play();
        void resultCB(const chess_msgs::Result::ConstPtr& goal);
};

ChessResult::ChessResult(std::string topic)
{
    result_sub_ = nh_.subscribe(topic, 1, &ChessResult::resultCB, this);
    std::string chess_move_topic;
    ros::param::get("~chess_move_topic", chess_move_topic);
    move_pub_ = nh_.advertise<chess_msgs::Move>(chess_move_topic, 1);
}
ChessResult::~ChessResult()
{
    ROS_INFO("~ChessResult");
}

void ChessResult::play() 
{
    ROS_INFO("begin pub chess move...");

    int move_id;
    double max_x, max_y;
    int type;
    double pick_x, pick_y, place_x, place_y;
    ros::param::get("~move_id", move_id);
    ros::param::get("~type", type);
    ros::param::get("~pick_x", pick_x);
    ros::param::get("~pick_y", pick_y);
    ros::param::get("~place_x", place_x);
    ros::param::get("~place_y", place_y);

    chess_msgs::Move move;
    move.move_id = move_id;
    chess_msgs::Operation op;
    op.type     = type;
    op.pick_x   = pick_x;
    op.pick_y   = pick_y;
    op.place_x  = place_x;
    op.place_y  = place_y;
    move.ops.push_back(op);

    ROS_INFO("move => move_id: %d", move.move_id);
    move_pub_.publish(move);
    
    ROS_INFO("end pub chess move.");
}

void ChessResult::resultCB(const chess_msgs::Result::ConstPtr& result) 
{
    ROS_INFO("result => move_id: %d, res: %d, msg: %s", result->move_id, result->res, result->msg.c_str());
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chess_result", ros::init_options::AnonymousName);
    // ros::AsyncSpinner spinner(1);
    // spinner.start();

    std::string chess_result_topic;
    ros::param::get("~chess_result_topic", chess_result_topic);

    ChessResult chess_result(chess_result_topic);
    double duration;
    ros::param::get("~duration", duration);
    ros::WallDuration(duration).sleep();
    chess_result.play();

    ROS_INFO("chess_result main.");
    // ros::waitForShutdown();
    ros::spin();
    return 0;
}