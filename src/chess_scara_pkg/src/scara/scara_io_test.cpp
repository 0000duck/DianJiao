#include <ros/ros.h>
#include "chess_scara_pkg/zmotion.h"

ZMC_HANDLE g_handle;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "scara_io_test");
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

    bool isOpen;
    ros::param::get("~isOpen", isOpen);

    char cmdbuff[2048];
    std::string value = isOpen ? "OFF" : "ON";
    //生成命令
    sprintf(cmdbuff, "OP(0,%s)", value.c_str());
    //调用命令执行函数
    iresult = ZMC_DirectCommand(g_handle, cmdbuff, NULL, 0);
    if (iresult == 0)
    {
        ROS_INFO("\t\t\tscara io call success.");
    }
    else
    {
        ROS_INFO("\t\t\tscara io call failure!");
        return false;
    }

    iresult = ZMC_Close(g_handle);
    if(0 == iresult)
    {
        ROS_INFO("zmotion close success.");
    }
    ros::shutdown();
    return 0;
}

