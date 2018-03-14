#include "chess_ur_pkg/ur_move.h"
#include <ros/ros.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "ur_move_test");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    int type;
    double pick_type, pick_x, pick_y, place_type, place_x, place_y;
    ros::param::get("~type", type);
    ros::param::get("~pick_type", pick_type);
    ros::param::get("~pick_x", pick_x);
    ros::param::get("~pick_y", pick_y);
    ros::param::get("~place_type", place_type);
    ros::param::get("~place_x", place_x);
    ros::param::get("~place_y", place_y);
    
    chess_msgs::Operation op;
    op.type = type;
    op.pick_type = pick_type;
    op.pick_x = pick_x;
    op.pick_y = pick_y;
    op.place_type = place_type;
    op.place_x = place_x;
    op.place_y = place_y;
    
    std::string group_name;
    ros::param::get("~group_name", group_name);

    UrMove ur_move(group_name);
    ur_move.play(op);

    ROS_INFO("ur_move_test main.");
    ros::shutdown();
    return 0;
}