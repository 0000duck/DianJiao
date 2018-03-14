#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <chess_msgs/StepAction.h>
#include <chess_msgs/Operation.h>

#include "chess_ur_pkg/ur_move.h"

class ChessActionServer
{
    protected:
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<chess_msgs::StepAction> as_;
        chess_msgs::StepFeedback feedback_;
        chess_msgs::StepResult result_;

        UrMove ur_move_;

    public:
        ChessActionServer(std::string action_name, std::string group_name);
        ~ChessActionServer(void);

        void goalCB();
        void preemptCB();
        void executeCB(const chess_msgs::StepGoalConstPtr &goal);

        void feedback(std::string feedback);
        void result(int res, std::string msg);
};

ChessActionServer::ChessActionServer(std::string action_name, std::string group_name) :
    // as_(nh_, name, boost::bind(&ChessActionServer::executeCB, this, _1), false)
    as_(nh_, action_name, false),
    ur_move_(group_name)
{
    as_.registerGoalCallback(boost::bind(&ChessActionServer::goalCB, this));
    as_.registerPreemptCallback(boost::bind(&ChessActionServer::preemptCB, this));
    as_.start();
}

ChessActionServer::~ChessActionServer(void)
{
}

 void ChessActionServer::goalCB()
{
    ROS_INFO("goal callback");
    const chess_msgs::StepGoalConstPtr goal = as_.acceptNewGoal();
    executeCB(goal);
}
void ChessActionServer::preemptCB()
{
    ROS_INFO("preempt callback");
}

void ChessActionServer::executeCB(const chess_msgs::StepGoalConstPtr &goal)
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
        bool success = ur_move_.play(op);
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

void ChessActionServer::feedback(std::string feedback)
{
    ROS_INFO("%s", feedback.c_str());
    feedback_.feedback = feedback;
    as_.publishFeedback(feedback_);
}

void ChessActionServer::result(int res, std::string msg)
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

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chess_action_server");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    std::string action_name, group_name;
    ros::param::get("~action_name", action_name);
    ros::param::get("~group_name", group_name);

    ChessActionServer chess_as(action_name, group_name);
    
    ROS_INFO("chess_action_server main.");
    ros::waitForShutdown();
    return 0;
}