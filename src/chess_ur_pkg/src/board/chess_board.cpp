#include <ros/ros.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/PlanningScene.h>
#include <moveit_msgs/ObjectColor.h>

class ChessBoard
{
  private:
    std::string _frame_id;

  protected:
    ros::NodeHandle nh_;
    ros::Publisher pub_co_;
    ros::Publisher pub_scene_;

  public:
    ChessBoard();
    ~ChessBoard();

    void setupDesk();
    void setupBoard();
    void setupCamera();
    
};

ChessBoard::ChessBoard()
{
  pub_co_ = nh_.advertise<moveit_msgs::CollisionObject>("collision_object", 10);
  pub_scene_ = nh_.advertise<moveit_msgs::PlanningScene>("planning_scene", 10);

  ros::param::get("~frame_id", _frame_id);
}
ChessBoard::~ChessBoard()
{
}

void ChessBoard::setupDesk()
{
  ROS_INFO("setup desk beginning...");
  ros::WallDuration(1).sleep();
  
  // 障碍物
  moveit_msgs::CollisionObject co;
  co.header.stamp = ros::Time::now();
  co.header.frame_id = _frame_id;

  shape_msgs::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  geometry_msgs::Pose pose;

  moveit_msgs::PlanningScene scene;
  scene.is_diff = true;
  moveit_msgs::ObjectColor oc;

  // 添加 Desk
  bool has_desk;
  std::string desk_id;
  ros::param::get("~has_desk", has_desk);
  ros::param::get("~desk_id", desk_id);
  double desk_height,desk_width,desk_depth;
  double desk_p_x,desk_p_y,desk_p_z;
  double desk_o_x,desk_o_y,desk_o_z,desk_o_w;
  ros::param::get("~desk_height", desk_height);
  ros::param::get("~desk_width", desk_width);
  ros::param::get("~desk_depth", desk_depth);
  ros::param::get("~desk_p_x", desk_p_x);
  ros::param::get("~desk_p_y", desk_p_y);
  ros::param::get("~desk_p_z", desk_p_z);
  ros::param::get("~desk_o_x", desk_o_x);
  ros::param::get("~desk_o_y", desk_o_y);
  ros::param::get("~desk_o_z", desk_o_z);
  ros::param::get("~desk_o_w", desk_o_w); 

  // remove
  co.id = desk_id;
  co.operation = co.REMOVE;
  pub_co_.publish(co);

  if(has_desk)
  {
      co.operation = co.ADD;
      // 尺寸
      primitive.dimensions[0] = desk_height;
      primitive.dimensions[1] = desk_width;
      primitive.dimensions[2] = desk_depth;
      // 位置
      pose.position.x = desk_p_x;
      pose.position.y = desk_p_y;
      pose.position.z = desk_p_z;
      pose.orientation.x = desk_o_x;
      pose.orientation.y = desk_o_y;
      pose.orientation.z = desk_o_z;
      pose.orientation.w = desk_o_w;
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);
      // set color
      oc.id = desk_id;
      oc.color.r = 1.0;
      oc.color.g = 1.0;
      oc.color.b = 1.0;
      oc.color.a = 1.0;
      scene.object_colors.push_back(oc);
      pub_scene_.publish(scene);
  }

  // 添加border
  bool has_border;
  std::string border1_id, border2_id, border3_id, border4_id;
  ros::param::get("~has_border", has_border);
  ros::param::get("~border1_id", border1_id);
  ros::param::get("~border2_id", border2_id);
  ros::param::get("~border3_id", border3_id);
  ros::param::get("~border4_id", border4_id);

  // remove
  co.id = border1_id;
  co.operation = co.REMOVE;
  pub_co_.publish(co);
  co.id = border2_id;
  co.operation = co.REMOVE;
  pub_co_.publish(co);
  co.id = border3_id;
  co.operation = co.REMOVE;
  pub_co_.publish(co);
  co.id = border4_id;
  co.operation = co.REMOVE;
  pub_co_.publish(co);

  if(has_border)
  { 
      pose.orientation.x = desk_o_x;
      pose.orientation.y = desk_o_y;
      pose.orientation.z = desk_o_z;
      pose.orientation.w = desk_o_w;

      // 添加border1
      double border1_height, border1_width, border1_depth;
      double border1_p_x, border1_p_y, border1_p_z;
      ros::param::get("~border1_height", border1_height);
      ros::param::get("~border1_width", border1_width);
      ros::param::get("~border1_depth", border1_depth);
      ros::param::get("~border1_p_x", border1_p_x);
      ros::param::get("~border1_p_y", border1_p_y);
      ros::param::get("~border1_p_z", border1_p_z);

      co.id = border1_id;
      co.operation = co.ADD;
      // 尺寸
      primitive.dimensions[0] = border1_height;
      primitive.dimensions[1] = border1_width;
      primitive.dimensions[2] = border1_depth;
      // 位置
      pose.position.x = border1_p_x;
      pose.position.y = border1_p_y;
      pose.position.z = border1_p_z;
      
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);

      // 添加border2
      double border2_height, border2_width, border2_depth;
      double border2_p_x, border2_p_y, border2_p_z;
      ros::param::get("~border2_height", border2_height);
      ros::param::get("~border2_width", border2_width);
      ros::param::get("~border2_depth", border2_depth);
      ros::param::get("~border2_p_x", border2_p_x);
      ros::param::get("~border2_p_y", border2_p_y);
      ros::param::get("~border2_p_z", border2_p_z);

      co.id = border2_id;
      co.operation = co.ADD;
      // 尺寸
      primitive.dimensions[0] = border2_height;
      primitive.dimensions[1] = border2_width;
      primitive.dimensions[2] = border2_depth;
      // 位置
      pose.position.x = border2_p_x;
      pose.position.y = border2_p_y;
      pose.position.z = border2_p_z;
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);

      // 添加border3
      double border3_height, border3_width, border3_depth;
      double border3_p_x, border3_p_y, border3_p_z;
      ros::param::get("~border3_height", border3_height);
      ros::param::get("~border3_width", border3_width);
      ros::param::get("~border3_depth", border3_depth);
      ros::param::get("~border3_p_x", border3_p_x);
      ros::param::get("~border3_p_y", border3_p_y);
      ros::param::get("~border3_p_z", border3_p_z);
      co.id = border3_id;
      co.operation = co.ADD;
      // 尺寸
      primitive.dimensions[0] = border3_height;
      primitive.dimensions[1] = border3_width;
      primitive.dimensions[2] = border3_depth;
      // 位置
      pose.position.x = border3_p_x;
      pose.position.y = border3_p_y;
      pose.position.z = border3_p_z;
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);

      // 添加border4
      double border4_height, border4_width, border4_depth;
      double border4_p_x, border4_p_y, border4_p_z;
      ros::param::get("~border4_height", border4_height);
      ros::param::get("~border4_width", border4_width);
      ros::param::get("~border4_depth", border4_depth);
      ros::param::get("~border4_p_x", border4_p_x);
      ros::param::get("~border4_p_y", border4_p_y);
      ros::param::get("~border4_p_z", border4_p_z);

      co.id = border4_id;
      co.operation = co.ADD;
      // 尺寸
      primitive.dimensions[0] = border4_height;
      primitive.dimensions[1] = border4_width;
      primitive.dimensions[2] = border4_depth;
      // 位置
      pose.position.x = border4_p_x;
      pose.position.y = border4_p_y;
      pose.position.z = border4_p_z;
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);
  }

  ros::WallDuration(1).sleep();
  ROS_INFO("setup desk end.");
}

void ChessBoard::setupBoard()
{
  ROS_INFO("setup board begin...");
  ros::WallDuration(1).sleep();

  moveit_msgs::CollisionObject co;
  co.header.stamp = ros::Time::now();
  co.header.frame_id = _frame_id;

  shape_msgs::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  geometry_msgs::Pose pose;

  moveit_msgs::PlanningScene scene;
  scene.is_diff = true;
  moveit_msgs::ObjectColor oc;
  
  // board
  bool has_board;
  std::string board_id;
  ros::param::get("~has_board", has_board);
  ros::param::get("~board_id", board_id);
  
  // remove
  co.id = board_id;
  co.operation  = co.REMOVE;
  pub_co_.publish(co);

  if(has_board)
  {
      co.operation  = co.ADD;

      double board_height, board_width, board_depth;
      double board_p_x, board_p_y, board_p_z;
      double board_o_x, board_o_y, board_o_z, board_o_w;

      ros::param::get("~board_height", board_height);
      ros::param::get("~board_width", board_width);
      ros::param::get("~board_depth", board_depth);
      ros::param::get("~board_p_x", board_p_x);
      ros::param::get("~board_p_y", board_p_y);
      ros::param::get("~board_p_z", board_p_z);
      ros::param::get("~board_o_x", board_o_x);
      ros::param::get("~board_o_y", board_o_y);
      ros::param::get("~board_o_z", board_o_z);
      ros::param::get("~board_o_w", board_o_w);

      primitive.dimensions[0] = board_height;
      primitive.dimensions[1] = board_width;
      primitive.dimensions[2] = board_depth;
      pose.position.x = board_p_x;
      pose.position.y = board_p_y;
      pose.position.z = board_p_z;
      pose.orientation.x = board_o_x;
      pose.orientation.y = board_o_y;
      pose.orientation.z = board_o_z;
      pose.orientation.w = board_o_w;
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);
      // set color
      oc.id = board_id;
      oc.color.r = 1.0;
      oc.color.g = 1.0;
      oc.color.b = 0.0;
      oc.color.a = 1.0;
      scene.object_colors.push_back(oc);
      
      pub_scene_.publish(scene);
  }
  
  ros::WallDuration(1).sleep();
  ROS_INFO("setup board end.");
}

void ChessBoard::setupCamera() 
{
  ROS_INFO("setup camera beginning...");
  ros::WallDuration(1).sleep();

  bool has_camera;
  std::string camera_id;
  ros::param::get("~has_camera", has_camera);
  ros::param::get("~camera_id", camera_id);
  
  // 障碍物  
  moveit_msgs::CollisionObject co;
  co.header.stamp = ros::Time::now();
  co.header.frame_id = _frame_id;

  shape_msgs::SolidPrimitive primitive;
  primitive.type = primitive.BOX;
  primitive.dimensions.resize(3);
  geometry_msgs::Pose pose;

  moveit_msgs::PlanningScene scene;
  scene.is_diff = true;
  moveit_msgs::ObjectColor oc;

  // remove
  co.id = camera_id;
  co.operation = co.REMOVE;
  pub_co_.publish(co);

  if(has_camera)
  {
      // 添加 Camera
      double camera_height, camera_width, camera_depth;
      double camera_p_x, camera_p_y, camera_p_z;
      double camera_o_x, camera_o_y, camera_o_z, camera_o_w;
      ros::param::get("~camera_height", camera_height);
      ros::param::get("~camera_width", camera_width);
      ros::param::get("~camera_depth", camera_depth);
      ros::param::get("~camera_p_x", camera_p_x);
      ros::param::get("~camera_p_y", camera_p_y);
      ros::param::get("~camera_p_z", camera_p_z);
      ros::param::get("~camera_o_x", camera_o_x);
      ros::param::get("~camera_o_y", camera_o_y);
      ros::param::get("~camera_o_z", camera_o_z);
      ros::param::get("~camera_o_w", camera_o_w);
      
      co.id = camera_id;
      co.operation = co.ADD;
      // 尺寸
      primitive.dimensions[0] = camera_height;
      primitive.dimensions[1] = camera_width;
      primitive.dimensions[2] = camera_depth;
      // 位置
      pose.position.x = camera_p_x;
      pose.position.y = camera_p_y;
      pose.position.z = camera_p_z;
      pose.orientation.x = camera_o_x;
      pose.orientation.y = camera_o_y;
      pose.orientation.z = camera_o_z;
      pose.orientation.w = camera_o_w;
      co.primitives.clear();
      co.primitive_poses.clear();
      co.primitives.push_back(primitive);
      co.primitive_poses.push_back(pose);
      pub_co_.publish(co);

      // set color
      oc.id = camera_id;
      oc.color.r = 0.0;
      oc.color.g = 0.0;
      oc.color.b = 0.0;
      oc.color.a = 1.0;
      scene.object_colors.push_back(oc);
      pub_scene_.publish(scene); 
  }

  ros::WallDuration(1).sleep();
  ROS_INFO("setup camera end.");
}


int main(int argc, char *argv[])
{
  ros::init(argc, argv, "chess_board");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  ChessBoard chess_board;
  chess_board.setupDesk();
  chess_board.setupBoard();
  chess_board.setupCamera();
  
  ROS_INFO("chess_board main.");
  ros::shutdown();
  return 0;
}
