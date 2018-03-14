#include <ros/ros.h>
#include <chess_msgs/Operation.h>
#include <chess_msgs/Play.h>

#include "chess_ur_pkg/ur_move.h"

class ChessServer
{
  protected:
    ros::NodeHandle nh_;
    ros::ServiceServer ss_;

    UrMove ur_move_;

  public:
    ChessServer(std::string srv_name, std::string group_name);
    ~ChessServer();

    bool play(chess_msgs::Play::Request& req,
              chess_msgs::Play::Response& resp);
};

ChessServer::ChessServer(std::string srv_name, std::string group_name) :
    ur_move_(group_name)
{
  ss_ = nh_.advertiseService(srv_name, &ChessServer::play, this);
}
ChessServer::~ChessServer()
{
}

bool ChessServer::play(chess_msgs::Play::Request& req,
                       chess_msgs::Play::Response& resp)
{
  ROS_WARN("###################### Service ########################");
  ROS_INFO("begin chess server...");
  bool success = true;
  for(int i = 0; i < req.ops.size(); i++) {
      chess_msgs::Operation op = req.ops[i];
      ROS_INFO("req type : %d pick : (%f, %f) place : (%f %f)", op.type, op.pick_x, op.pick_y, op.place_x, op.place_y);

      ros::AsyncSpinner spinner(1);
      spinner.start();
      success = ur_move_.play(op);
      spinner.stop();

      if(!success){
        resp.res = -1;
        resp.msg = "play fialure";
        ROS_INFO("play failure.");
        return false; 
      }
      ROS_INFO("play success.");
  }
  if(success) {
    resp.res = 1;
    resp.msg = "success";
  }

  ROS_INFO("end chess server.");
  return true;
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "chess_server");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  std::string srv_name, group_name;
  ros::param::get("~srv_name", srv_name);
  ros::param::get("~group_name", group_name);

  ChessServer chess_server(srv_name, group_name);

  ROS_INFO("chess_server main.");
  ros::waitForShutdown();
  return 0;
}