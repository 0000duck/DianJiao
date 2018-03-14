#include "ros/ros.h"
#include "chess_msgs/Mode.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "scara_switch_mode");

  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<chess_msgs::Mode>("scara_switch_mode");

  bool manual;
  ros::param::get("~manual", manual);

  chess_msgs::Mode srv;
  srv.request.manual = manual;
  if (client.call(srv))
  {
    ROS_INFO("success switch mode (%d)", srv.response.result);
  }
  else
  {
    ROS_ERROR("failure switch mode");
    return 1;
  }
  
  return 0;
}