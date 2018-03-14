#include "chess_scara_pkg/scara_move.h"
#include "chess_scara_pkg/zaux.h"

void logOperation(chess_msgs::Operation &op)
{
    ROS_INFO("type: %d, pick[%d - (%f, %f)] ==>  place[%d - (%f, %f)]", op.type, op.pick_type, op.pick_x, op.pick_y, op.place_type, op.place_x, op.place_y);
}

void logPose(chess_msgs::Zpose &pose)
{
    ROS_INFO("Zpose(%f, %f, %f, %f)", pose.x, pose.y, pose.z, pose.r);
}

void ScaraMove::logCurrentPose(std::string str)
{
    chess_msgs::Zpose pose = this->get_point();
    ROS_INFO("%sZpose(%f, %f, %f, %f)", str.c_str(), pose.x, pose.y, pose.z, pose.r);
}

ScaraMove::ScaraMove()
{
    std::string robot_ip;
    ros::param::get("~robot_ip", robot_ip);

    char *ipaddr = new char[20];
    strcpy(ipaddr, robot_ip.c_str());

    int32 iresult = ZMC_OpenEth(ipaddr, &g_handle_);
    ROS_INFO("ScaraMove zmotion result: %d", iresult);
    if(0 == iresult)
    {
        ROS_INFO("ScaraMove zmotion connect success.");
    }
    
    // 获取配置参数
    ros::param::get("~sleep", sleep);
    ros::param::get("~up_height", up_height);
    ros::param::get("~position_z", position_z);
    ros::param::get("~place_offset", place_offset);
    ros::param::get("~wait_x", wait_x);
    ros::param::get("~wait_y", wait_y);
    ros::param::get("~wait_r", wait_r);
    ros::param::get("~wait_z", wait_z);

    ros::param::get("~far_r", far_r);
    ros::param::get("~near_r", near_r);
    
}
ScaraMove::~ScaraMove()
{
    int32 iresult = ZMC_Close(g_handle_);
    if(0 == iresult)
    {
        ROS_INFO("zmotion close success.");
    }
}

chess_msgs::Zpose ScaraMove::get_point()
{
    chess_msgs::Zpose pose;
    float dpos6 = 0.0;
    float dpos7 = 0.0;
    float dpos8 = 0.0;
    float dpos9 = 0.0;
    ZAux_Direct_GetDpos(g_handle_, 6, &dpos6);
    ZAux_Direct_GetDpos(g_handle_, 7, &dpos7);
    ZAux_Direct_GetDpos(g_handle_, 8, &dpos8);
    ZAux_Direct_GetDpos(g_handle_, 9, &dpos9);
    pose.x = dpos6;
    pose.y = dpos7;
    pose.r = dpos8;
    pose.z = dpos9;

    return pose;
}

bool ScaraMove::switch_mode(bool manual)
{
    uint16 num_axis = 4;
    int reaxislist[4] = {0,1,2,3};  // 关节轴
    int axislist[4] = {6,7,8,9};    // 虚拟轴
    
    if(manual) // 手动模式
    {
      ZAux_Direct_Base(g_handle_, num_axis, axislist);
      ZAux_Direct_Connreframe(g_handle_, 1, 0, num_axis, reaxislist);
    }
    else 
    {
      ZAux_Direct_Base(g_handle_, num_axis, reaxislist);
      ZAux_Direct_Connframe(g_handle_, 1, 0, num_axis, axislist);
    }

    char cmdbuff[2048];
    int value = manual ? 0 : 1;
    //生成命令
    sprintf(cmdbuff, "WDOG=%d", value);
    //调用命令执行函数
    int iresult = ZMC_DirectCommand(g_handle_, cmdbuff, NULL, 0);
    if (iresult == 0)
    {
        ROS_INFO("\t\t\tscara wdog call success.");
    }
    else
    {
        ROS_INFO("\t\t\tscara wdog call failure!");
        return false;
    }
    return true;
}

bool ScaraMove::play(chess_msgs::Operation &op)
{   
    ROS_WARN(">>>>>>>>>>>>>>> Begin Operation >>>>>>>>>>>>>>>>>>>>>>>");
    logOperation(op);
    
    switch(op.type) 
    {
        case 0: // 走棋
            if(!this->go(op)) return false;
            break;
        case 1: // 吃子
            if(!this->capture(op)) return false;
            break;
        case 2: // 回等待位
            if(!this->wait()) return false;
            break;
    }

    ROS_WARN(">>>>>>>>>>>>>>> End Operation. >>>>>>>>>>>>>>>>>>>>>>>");
    return true;
}

// 走棋
bool ScaraMove::go(chess_msgs::Operation &op)
{
    ROS_INFO("\tbegin go...");
    
    // 抓棋
    if(!this->pick(op)) 
        return false;

    // 放到目的位置
    chess_msgs::Zpose pose; 
    pose.x = op.place_x;
    pose.y = op.place_y;
    pose.z = position_z;
    pose.r = op.place_type == 0 ? far_r : near_r;
    logPose(pose);
     
    // 移动到目标位置
    if(!this->movePath(pose))
        return false;
   
    // 打开转手
    //this->controlGripper(true);
    // 抬手
    //this->moveUp(pose);
    
   
 

    ROS_INFO("\tend go."); 
    return true;
} 



// 吃棋     
bool ScaraMove::capture(chess_msgs::Operation &op)
{
    ROS_INFO("\tbegin capture...");

    // 抓棋
    if(!this->pick(op)) 
        return false;

    // 放到等待位置
    chess_msgs::Zpose pose;
    pose.x = wait_x;
    pose.y = wait_y;
    pose.z = wait_z;
    pose.r = wait_r;
    logPose(pose);
    // 移动
    if(!this->movePath(pose))
        return false;
    // 打开转手
    this->controlGripper(true);
    
    ROS_INFO("\tend capture.");
    return true;
}

// 回等待位
bool ScaraMove::wait() 
{
    ROS_INFO("\tbegin wait...");


    
    // 设置目标位姿
    chess_msgs::Zpose pose;
    pose.x = wait_x;
    pose.y = wait_y;
    pose.z = wait_z;
    pose.r = wait_r;
    this->moveUp(pose);
    // 移动
    if(!this->movePath(pose))
        return false;
    
    ROS_INFO("\tend wait.");
    return true;
}


bool ScaraMove::pick(chess_msgs::Operation &op)
{       
    ROS_INFO("\tbegin pick...");

    // 1> 打开抓手
    //this->controlGripper(true);
    
    // 设置目标位姿
    chess_msgs::Zpose pose;
    pose.x = op.pick_x;
    pose.y = op.pick_y;
    pose.z = position_z;
    pose.r = op.pick_type == 0 ? far_r : near_r;
    
    // 2> 向下移动到目标位置
    if(!this->movePath(pose))
        return false;
    
    // 3> 关闭抓手
    //this->controlGripper(false);

    // 4> 抬手
    //this->moveUp(pose);

    ROS_INFO("\tend pick.");

    return true;
}

bool ScaraMove::controlGripper(bool isOpen)
{   
    ROS_INFO("\t\tbegin control gripper...");

    ros::WallDuration(sleep).sleep();

    int32 iresult;
    char cmdbuff[2048];
    std::string value = isOpen ? "OFF" : "ON";
    //生成命令
    sprintf(cmdbuff, "OP(0,%s)", value.c_str());
    //调用命令执行函数
    iresult = ZMC_DirectCommand(g_handle_, cmdbuff, NULL, 0);

    this->waitIDLE();

    if (iresult == 0)
    {
        ROS_INFO("\t\t\tscara io call success.");
    }
    else
    {
        ROS_INFO("\t\t\tscara io call failure!");
        return false;
    }
    ROS_INFO("\t\tend control gripper.");

    return true;
}

bool ScaraMove::moveUp(chess_msgs::Zpose &pose)
{
    ROS_INFO("\t\tbegin move up...");
    this->logCurrentPose("\t\t\t");
    
    int32 iresult;
    uint16 num_axis = 1;
    int axislist[1] = {9}; //轴列表
    float poslist[1]= {up_height};
    
    // iresult = ZAux_Direct_Base(g_handle_, num_axis, axislist);
    // iresult = ZAux_Direct_MoveAbs(g_handle_, num_axis, poslist);
    iresult = ZAux_Direct_BaseAndMoveAbs(g_handle_, num_axis, axislist, poslist);

    this->waitIDLE();

    if(iresult != 0)
      return false;

    this->logCurrentPose("\t\t\t");
    ROS_INFO("\t\tend move up.");
    return true;
}

bool ScaraMove::movePath(chess_msgs::Zpose &pose) {
    ROS_INFO("\t\tbegin move Path...");
    
    // 移动XY
    if(!this->moveXY(pose))
        return false;
    
    // 移动Z
    if(!this->moveZ(pose))
        return false;
    
    ROS_INFO("\t\tend move Path.");
    return true;
}

bool ScaraMove::moveXY(chess_msgs::Zpose &pose)
{
    ROS_INFO("\t\t\tbegin move XY...");
    this->logCurrentPose("\t\t\t\t");

    int32 iresult;
    uint16 num_axis = 3;
    int axislist[3] = {6,7,8}; //轴列表
    float poslist[3]= {pose.x, pose.y, pose.r};
    
    // iresult = ZAux_Direct_Base(g_handle_, num_axis, axislist);
    // iresult = ZAux_Direct_MoveAbs(g_handle_, num_axis, poslist);
    iresult = ZAux_Direct_BaseAndMoveAbs(g_handle_, num_axis, axislist, poslist);
    
    this->waitIDLE();

    ROS_INFO("result : %d", iresult);
    if(iresult != 0)
      return false;

    this->logCurrentPose("\t\t\t\t");
    ROS_INFO("\t\t\tend move XY.");
    return true;
}

bool ScaraMove::moveZ(chess_msgs::Zpose &pose)
{
    ROS_INFO("\t\t\tbegin move Z...");
    this->logCurrentPose("\t\t\t\t");
    
    int32 iresult;
    uint16 num_axis = 1;
    int axislist[1] = {9}; //轴列表
    float poslist[1]= {pose.z};
    
    // iresult = ZAux_Direct_Base(g_handle_, num_axis, axislist);
    // iresult = ZAux_Direct_MoveAbs(g_handle_, num_axis, poslist);
    iresult = ZAux_Direct_BaseAndMoveAbs(g_handle_, num_axis, axislist, poslist);
    
    this->waitIDLE();

    if(iresult != 0)
      return false;

    this->logCurrentPose("\t\t\t\t");
    ROS_INFO("\t\t\tend move Z.");
    return true;
}

void ScaraMove::waitIDLE()
{
    ROS_INFO("\t\tbegin wait idle...");

    int run_state = 0;
    do {
      ZAux_Direct_GetIfIdle(g_handle_, 6, &run_state);
    } while(run_state == 0); 

    // int32 iresult;
    // char cmdbuff[2048];
    // std::string cmd = "Wait unitl idle(6) and idle(7) and idle(8) and idle(9)";
    // //生成命令
    // strcpy(cmdbuff, cmd.c_str());
    // //调用命令执行函数
    // iresult = ZMC_DirectCommand(g_handle_, cmdbuff, NULL, 0);
    // if (iresult == 0)
    // {
    //     ROS_INFO("\t\t\tidle success.");
    // }
    // else
    // {
    //     ROS_INFO("\t\t\tidle failure!");
    // }
    ROS_INFO("\t\tend wait idle.");
}
