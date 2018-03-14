#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <chess_msgs/StepAction.h>
#include <chess_msgs/Operation.h>

class ChessScaraClient
{
  protected:
    actionlib::SimpleActionClient<chess_msgs::StepAction> ac_;
    
  public:
    ChessScaraClient(std::string name);
    ~ChessScaraClient();

    void doStep();
    
    void doneCB(const actionlib::SimpleClientGoalState& state,
                const chess_msgs::StepResultConstPtr& result);
    void activeCB();
    void feedbackCB(const chess_msgs::StepFeedbackConstPtr& feedback);

};

ChessScaraClient::ChessScaraClient(std::string name) :
  ac_(name, true)
{
  ROS_INFO("Waiting for chess scara server to start...");
  ac_.waitForServer();
  ROS_INFO("Chess scara server started, sending goal.");
}
ChessScaraClient::~ChessScaraClient()
{
}

void ChessScaraClient::doStep()
{   
    int type, pick_type, place_type;
    double pick_x, pick_y, place_x, place_y;
    ros::param::get("~type", type);
    ros::param::get("~pick_type", pick_type);
    ros::param::get("~pick_x", pick_x);
    ros::param::get("~pick_y", pick_y);
    ros::param::get("~place_type", place_type);
    ros::param::get("~place_x", place_x);
    ros::param::get("~place_y", place_y);
    
    chess_msgs::StepGoal goal;
    chess_msgs::Operation op;
    op.type = type;
    op.pick_type = pick_type;
    op.pick_x = pick_x;
    op.pick_y = pick_y;
    op.place_type = place_type;
    op.place_x = place_x;
    op.place_y = place_y;
    goal.ops.push_back(op);
    
    ROS_INFO("Send goal =>");
    std::cout << goal << std::endl;
    // send goal
    ac_.sendGoal(goal, boost::bind(&ChessScaraClient::doneCB, this, _1, _2),       boost::bind(&ChessScaraClient::activeCB, this), boost::bind(&ChessScaraClient::feedbackCB, this, _1));
}

void ChessScaraClient::doneCB(const actionlib::SimpleClientGoalState& state,
                const chess_msgs::StepResultConstPtr& result)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
  ROS_INFO("Chess res : %d ; msg : %s", result->res, result->msg.c_str());
  // ros::shutdown();
}

void ChessScaraClient::activeCB()
{
  ROS_INFO("Chess active.");
}

void ChessScaraClient::feedbackCB(const chess_msgs::StepFeedbackConstPtr& feedback)
{
  ROS_INFO("Chess feedback : %s", feedback->feedback.c_str());
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "chess_scara_client", ros::init_options::AnonymousName);
  ros::AsyncSpinner spinner(1);
  spinner.start();

  std::string action_name;
  ros::param::get("~action_name", action_name);

  ChessScaraClient chess_ac(action_name);
  chess_ac.doStep();

  ROS_INFO("chess_scara_client main.");
  ros::waitForShutdown();
  // ros::spin();
  return 0;
}
