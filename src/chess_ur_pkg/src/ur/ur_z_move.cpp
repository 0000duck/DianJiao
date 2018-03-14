#include <ros/ros.h>
#include "chess_ur_pkg/ur_move.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "ur_ik_move");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    UrMove urmove("manipulator");
    urmove.testMoveZ();
    
    ros::shutdown();
    return 0;
}