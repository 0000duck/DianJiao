#include "ros/ros.h"
#include "chess_msgs/Point.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ur_get_point_test");

  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<chess_msgs::Point>("ur_get_point");
  chess_msgs::Point srv;
  if (client.call(srv))
  {
    ROS_INFO("success point(%f, %f)", srv.response.x, srv.response.y);
  }
  else
  {
    ROS_ERROR("failure");
    return 1;
  }
  
  return 0;
}