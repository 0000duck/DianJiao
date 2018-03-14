#include <ros/ros.h>
#include <chess_msgs/Move.h>
#include <chess_msgs/Result.h>
#include <chess_msgs/Operation.h>

#include "chess_ur_pkg/ur_move.h"

class ChessMove
{
    protected:
        ros::NodeHandle nh_;
        ros::Subscriber move_sub_;
        ros::Publisher result_pub_;

        UrMove ur_move_;

    public:
        ChessMove(std::string topic, std::string group_name);
        ~ChessMove();
        
        void moveCB(const chess_msgs::Move::ConstPtr& goal);
        void result(int move_id, bool res, std::string msg);
};

ChessMove::ChessMove(std::string topic, std::string group_name) :
    ur_move_(group_name)
{
    move_sub_ = nh_.subscribe(topic, 1, &ChessMove::moveCB, this);
    std::string chess_result_topic;
    ros::param::get("~chess_result_topic", chess_result_topic);
    result_pub_ = nh_.advertise<chess_msgs::Result>(chess_result_topic, 1);
}
ChessMove::~ChessMove()
{
    ROS_INFO("~ChessMove");
}

void ChessMove::moveCB(const chess_msgs::Move::ConstPtr& move)
{
    ROS_WARN("####################### Topic #######################");
    ROS_INFO("begin chess move...");
    for(int i = 0; i < move->ops.size(); i++) {
        chess_msgs::Operation op = move->ops[i];
        ROS_INFO("op => type: %d, pick: (%f, %f), place: (%f %f)", op.type, op.pick_x, op.pick_y, op.place_x, op.place_y);
        
        ros::AsyncSpinner spinner(1);
        spinner.start();
        bool success = ur_move_.play(op);
        spinner.stop();

        if(!success){
            this->result(move->move_id, false, "chess move failure!");
            return;   
        }
    }
    this->result(move->move_id, true, "chess move success!");
    ROS_INFO("end chess move.");
}

void ChessMove::result(int move_id, bool res, std::string msg) 
{
    ROS_INFO("begin pub chess result.");
    ROS_INFO("result => move_id: %d, res: %d, msg: %s", move_id, res, msg.c_str());
    chess_msgs::Result result;
    result.move_id = move_id;
    result.res = res;
    result.msg = msg;

    result_pub_.publish(result);
    ROS_INFO("end pub chess result.");
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chess_move");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    std::string chess_move_topic, group_name;
    ros::param::get("~chess_move_topic", chess_move_topic);
    ros::param::get("~group_name", group_name);

    ChessMove chess_move(chess_move_topic, group_name);
    
    ROS_INFO("chess_move main.");
    ros::waitForShutdown();
    return 0;
}