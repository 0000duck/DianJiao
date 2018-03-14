#include <ros/ros.h>
#include <chess_msgs/Point.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/PoseStamped.h>

class UrGetPoint
{
  protected:
    ros::NodeHandle nh_;
    ros::ServiceServer ss_;
    moveit::planning_interface::MoveGroupInterface move_group_;

  public:
    UrGetPoint(std::string srv_name, std::string group_name);
    ~UrGetPoint();

    bool get_point(chess_msgs::Point::Request& req,
              chess_msgs::Point::Response& resp);
};

UrGetPoint::UrGetPoint(std::string srv_name, std::string group_name) :
    move_group_(group_name)
{
  ss_ = nh_.advertiseService(srv_name, &UrGetPoint::get_point, this);
}
UrGetPoint::~UrGetPoint()
{
}

bool UrGetPoint::get_point(chess_msgs::Point::Request& req,
                       chess_msgs::Point::Response& resp)
{
  ROS_INFO("begin get_point server...");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  std::string end_effector_link = move_group_.getEndEffectorLink();
  std::cout << end_effector_link;
  ROS_INFO("%s, %s", end_effector_link.c_str(), move_group_.getPlanningFrame().c_str());

  geometry_msgs::PoseStamped ps = move_group_.getCurrentPose();
  resp.x = ps.pose.position.x;
  resp.y = ps.pose.position.y;

  spinner.stop();

  ROS_INFO("end get_point server.");
  return true;
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "ur_get_point");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  std::string srv_name, group_name;
  ros::param::get("~srv_name", srv_name);
  ros::param::get("~group_name", group_name);

  UrGetPoint ur_get_point(srv_name, group_name);

  ROS_INFO("ur_get_point main.");
  ros::waitForShutdown();
  return 0;
}