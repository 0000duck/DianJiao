#!/usr/bin/env python

import rospy, sys
import moveit_commander
from moveit_commander import MoveGroupCommander

from chess_msgs.srv import *

def get_ur_pose(req):
    manipulator = MoveGroupCommander('manipulator')
    end_effector_link = manipulator.get_end_effector_link()       
    ee_pose = manipulator.get_current_pose(end_effector_link)
    rospy.loginfo("End effector pose:\n" + str(ee_pose))
    resp = PointResponse()
    resp.x = ee_pose.pose.position.x
    resp.y = ee_pose.pose.position.y
    return resp
    
if __name__ == "__main__":
    rospy.init_node("ur_get_point_py")
    s = rospy.Service('ur_get_point_py', Point, get_ur_pose)
    rospy.loginfo("ur_get_point_py server start.")
    rospy.spin()
    