#ifndef CHESS_SCARA_PKG_SCARA_MOVE_H
#define CHESS_SCARA_PKG_SCARA_MOVE_H

#include <ros/ros.h>
#include "chess_msgs/Zpose.h"
#include "chess_msgs/Operation.h"
#include "chess_scara_pkg/zmotion.h"



class ScaraMove {
  private:
    
    float sleep;
    float up_height;
    float position_z;
    float place_offset;
    float wait_x, wait_y, wait_r, wait_z;
    float near_r, far_r;

    void logCurrentPose(std::string str);
    
    bool go(chess_msgs::Operation &op);         // 走棋
    bool capture(chess_msgs::Operation &op);    // 吃棋
    bool wait();                                // 回等待位置

    bool pick(chess_msgs::Operation &op);       // 抓棋
    bool controlGripper(bool isOpen);           // 控制抓手
    
    bool moveUp(chess_msgs::Zpose &pose);
    
    bool movePath(chess_msgs::Zpose &pose);
    
    bool moveXY(chess_msgs::Zpose &pose);   
    bool moveZ(chess_msgs::Zpose &pose);

    void waitIDLE();

  protected:
    ros::NodeHandle nh_;
    ZMC_HANDLE g_handle_;

  public:
    ScaraMove();
    ~ScaraMove();
    
    bool play(chess_msgs::Operation &op);

    chess_msgs::Zpose get_point();
    bool switch_mode(bool manual);
};

#endif
