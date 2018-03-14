#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <chess_msgs/Play.h>

class ChessClient
{
  protected:
    ros::NodeHandle nh_;
    ros::ServiceClient sc_;

  public:
    ChessClient(std::string srv_name);
    ~ChessClient();

    void play();
};

ChessClient::ChessClient(std::string srv_name)
{
  sc_ = nh_.serviceClient<chess_msgs::Play>(srv_name);
}
ChessClient::~ChessClient()
{
}

void ChessClient::play()
{
  ROS_INFO("begin chess client...");

  int type;
  double pick_x, pick_y, place_x, place_y;
  ros::param::get("~type", type);
  ros::param::get("~pick_x", pick_x);
  ros::param::get("~pick_y", pick_y);
  ros::param::get("~place_x", place_x);
  ros::param::get("~place_y", place_y);

  chess_msgs::Play play;
  chess_msgs::Operation op;
  op.type     = type;
  op.pick_x   = pick_x;
  op.pick_y   = pick_y;
  op.place_x  = place_x;
  op.place_y  = place_y;
  play.request.ops.push_back(op);

  if (sc_.call(play))
  {
    ROS_INFO("play success : %d %s", play.response.res, play.response.msg.c_str());
  }
  else
  {
    ROS_INFO("play failure : %d %s", play.response.res, play.response.msg.c_str() );
  }
  
  ROS_INFO("end chess client.");
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "chess_client", ros::init_options::AnonymousName);
  // ros::AsyncSpinner spinner(1);
  // spinner.start();

  std::string srv_name;
  ros::param::get("~srv_name", srv_name);

  ChessClient chess_client(srv_name);
  chess_client.play();
  
  ROS_INFO("chess_client main.");
  // ros::shutdown();
  ros::spin();
  return 0;
}