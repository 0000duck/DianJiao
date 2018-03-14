#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <chess_msgs/StepAction.h>
#include <chess_msgs/Operation.h>

#include <chess_msgs/Point.h>
#include <chess_msgs/Mode.h>

#include "chess_scara_pkg/scara_move.h"
#include "chess_msgs/Zpose.h"

class ChessScaraServer
{
    protected:
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<chess_msgs::StepAction> as_;
        chess_msgs::StepFeedback feedback_;
        chess_msgs::StepResult result_;

        ros::ServiceServer point_ss_;
        ros::ServiceServer mode_ss_;

        ScaraMove scara_move_;

    public:
        ChessScaraServer(std::string action_name);
        ~ChessScaraServer(void);

        void goalCB();
        void preemptCB();
        void executeCB(const chess_msgs::StepGoalConstPtr &goal);

        void feedback(std::string feedback);
        void result(int res, std::string msg);

        bool get_point(chess_msgs::Point::Request& req,
              chess_msgs::Point::Response& resp);
        bool switch_mode(chess_msgs::Mode::Request& req,
              chess_msgs::Mode::Response& resp);
};

ChessScaraServer::ChessScaraServer(std::string action_name) :
    // as_(nh_, name, boost::bind(&ChessScaraServer::executeCB, this, _1), false)
    as_(nh_, action_name, false)
{
    as_.registerGoalCallback(boost::bind(&ChessScaraServer::goalCB, this));
    as_.registerPreemptCallback(boost::bind(&ChessScaraServer::preemptCB, this));
    as_.start();

    std::string point_srv_name, mode_srv_name;
    ros::param::get("~point_srv_name", point_srv_name);
    ros::param::get("~mode_srv_name", mode_srv_name);

    point_ss_ = nh_.advertiseService(point_srv_name, &ChessScaraServer::get_point, this);
    mode_ss_ = nh_.advertiseService(mode_srv_name, &ChessScaraServer::switch_mode, this);

}

ChessScaraServer::~ChessScaraServer(void)
{
}

 void ChessScaraServer::goalCB()
{
    ROS_INFO("goal callback");
    const chess_msgs::StepGoalConstPtr goal = as_.acceptNewGoal();
    executeCB(goal);
}
void ChessScaraServer::preemptCB()
{
    ROS_INFO("preempt callback");
}

void ChessScaraServer::executeCB(const chess_msgs::StepGoalConstPtr &goal)
{
    ROS_WARN("##################### Action #########################");
    ROS_INFO("start execute chess step goal...");
    std::cout << goal;
    feedback_.feedback = "";
    result_.res = 0;
    result_.msg = "";

    if (!as_.isActive()) 
    {
        ROS_INFO("chess goal cancel.");
        return;
    }
    
    for(int i = 0; i < goal->ops.size(); i++) {
        if (as_.isPreemptRequested() || !ros::ok())
        {
            result(1, "chess action preempted");
            break;
        }
        
        chess_msgs::Operation op = goal->ops[i];
        ROS_INFO("op => type: %d, pick: (%f, %f), place: (%f %f)", op.type, op.pick_x, op.pick_y, op.place_x, op.place_y);

        ros::AsyncSpinner spinner(1);
        spinner.start();
        bool success = scara_move_.play(op);
        spinner.stop();
        
        if(!success){
            feedback("play failure.");
            result_.res = -1;
            break;
        }
    }

    if(result_.res == 0) {
        result(0, "step success.");
    } else {
        result(-1, "step failure.");
    }
    
    ROS_INFO("end execute chess step goal");
}

void ChessScaraServer::feedback(std::string feedback)
{
    ROS_INFO("%s", feedback.c_str());
    feedback_.feedback = feedback;
    as_.publishFeedback(feedback_);
}

void ChessScaraServer::result(int res, std::string msg)
{
    ROS_INFO("res: %d ; msg: %s", res, msg.c_str());
    result_.msg = msg;
    if(res == 0) // success
    {
        result_.res = true;
        as_.setSucceeded(result_);
    } 
    else if(res == 1)
    {
        result_.res = false;
        as_.setPreempted(result_);
    }
    else // aborted
    {
        result_.res = false;
        as_.setAborted(result_);
    }
}

bool ChessScaraServer::get_point(chess_msgs::Point::Request& req,
                       chess_msgs::Point::Response& resp)
{
  ROS_INFO("begin get_point server...");
  chess_msgs::Zpose pose = scara_move_.get_point();
  resp.x = pose.x;
  resp.y = pose.y;
  ROS_INFO("end get_point server.");
  return true;
}

bool ChessScaraServer::switch_mode(chess_msgs::Mode::Request& req,
              chess_msgs::Mode::Response& resp)
{
  ROS_INFO("begin switch_mode server...");
  bool result = scara_move_.switch_mode(req.manual);
  resp.result = result;
  if(!result)
    return false;
  ROS_INFO("end switch_mode server.");
  return true;
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chess_scara_server");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    std::string action_name;
    ros::param::get("~action_name", action_name);
    
    ChessScaraServer chess_as(action_name);
    
    ROS_INFO("chess_scara_server main.");
    ros::waitForShutdown();
    return 0;
}