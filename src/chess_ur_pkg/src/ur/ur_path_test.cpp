#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit/robot_trajectory/robot_trajectory.h>
#include <moveit/trajectory_processing/iterative_time_parameterization.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ur_path_test");
  ros::NodeHandle node_handle;  
  ros::AsyncSpinner spinner(1);
  spinner.start();
  
  moveit::planning_interface::MoveGroupInterface group("manipulator");
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;  

  ros::Publisher display_publisher = node_handle.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  moveit_msgs::DisplayTrajectory display_trajectory;

  moveit::planning_interface::MoveGroupInterface::Plan plan;
  group.setStartStateToCurrentState();

  std::vector<geometry_msgs::Pose> waypoints;

  geometry_msgs::Pose target_pose = group.getCurrentPose().pose;
  target_pose.position.x += 0.0;
  target_pose.position.y += 0.05;
  target_pose.position.z -= 0.02;
  waypoints.push_back(target_pose);  

  target_pose.position.y -= 0.0;
  waypoints.push_back(target_pose); 

  target_pose.position.z -= 0.08;
  target_pose.position.y += 0.0;
  target_pose.position.x -= 0.0;
  waypoints.push_back(target_pose);  

  moveit_msgs::RobotTrajectory trajectory_msg;
  group.setPlanningTime(10.0);
  
  double fraction = group.computeCartesianPath(waypoints,
                                               0.01,  // eef_step
                                               0.0,   // jump_threshold
                                               trajectory_msg, false);
  
  // The trajectory needs to be modified so it will include velocities as well.
  // First to create a RobotTrajectory object
  robot_trajectory::RobotTrajectory rt(group.getCurrentState()->getRobotModel(), "manipulator");

  // Second get a RobotTrajectory from trajectory
  rt.setRobotTrajectoryMsg(*group.getCurrentState(), trajectory_msg);
  
  // Thrid create a IterativeParabolicTimeParameterization object
  trajectory_processing::IterativeParabolicTimeParameterization iptp;
  // Fourth compute computeTimeStamps
  bool success = iptp.computeTimeStamps(rt);
  ROS_INFO("Computed time stamp %s",success?"SUCCEDED":"FAILED");
  // Get RobotTrajectory_msg from RobotTrajectory
  rt.getRobotTrajectoryMsg(trajectory_msg);
  // Check trajectory_msg for velocities not empty
  std::cout << trajectory_msg << std::endl;
  
  plan.trajectory_ = trajectory_msg;
  ROS_INFO("Visualizing plan 4 (cartesian path) (%.2f%% acheived)",fraction * 100.0);    
  sleep(1.0);
  
  group.execute(plan);  

  ros::shutdown();  
  return 0;
}