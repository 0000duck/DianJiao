#include <ros/ros.h>
#include "chess_scara_pkg/zmotion.h"
#include "chess_scara_pkg/zaux.h"

ZMC_HANDLE g_handle;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "scara_zmotion_test");
    ros::AsyncSpinner spinner(1);
    spinner.start();

    std::string ip;
    ros::param::get("~ip", ip);

    char *ipaddr = new char[20];
    strcpy(ipaddr, ip.c_str());

    int32 iresult = ZMC_OpenEth(ipaddr, &g_handle);
    ROS_INFO("zmotion result: %d", iresult);
    if(0 == iresult)
    {
        ROS_INFO("zmotion connect success.");
    }

    float x,y,r,z;
    ros::param::get("~x", x);
    ros::param::get("~y", y);
    ros::param::get("~r", r);
    ros::param::get("~z", z);
    
    uint16 num_axis = 4;
    int axislist[4] = {6,7,8,9}; //轴列表
    float poslist[4]= {x,y,r,z};
    
    ZAux_Direct_Base(g_handle, num_axis, axislist);
    ZAux_Direct_MoveAbs(g_handle, num_axis, poslist);

    iresult = ZMC_Close(g_handle);
    if(0 == iresult)
    {
        ROS_INFO("zmotion close success.");
    }
    ros::shutdown();
    return 0;
}

