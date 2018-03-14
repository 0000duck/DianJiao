#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @File    : python main.py
# @Desc    :


import math
import pickle
from tkMessageBox import *
from std_msgs.msg import String
import rospy
def _axis((x1,y1), (x2,y2), (a1, b1), (a2, b2), (x3, y3)):

    a1 = a1 * 1000
    a2 = a2 * 1000
    b1 = b1 * 1000
    b2 = b2 * 1000

    x, y = x2 - x1, y2 - y1
    a, b = a2 - a1, b2 - b1

    x3, y3 = x3 - x1, y3 - y1
    len_xy = math.sqrt(x * x + y * y)
    len_ab = math.sqrt(a * a + b * b)

    nx3 = x3 * len_ab / len_xy
    ny3 = y3 * len_ab / len_xy

    ang = math.atan2(y, x)
    ang = ang - math.atan2(b, a)

    na3 = nx3 * math.cos(ang) + ny3 * math.sin(ang)
    nb3 = ny3 * math.cos(ang) - nx3 * math.sin(ang)
    return (a1 + na3)/1000, (b1 + nb3)/1000


def axis(point):
    pub_command = rospy.Publisher('judgeError', String, queue_size=1)
    path = rospy.get_param('~path')
    robot_id = rospy.get_param('~robot_id')
    data = None
    try:
        pkl_file = open(path + robot_id + '_' +'mark.txt', 'rb')
        data = pickle.load(pkl_file)
        pkl_file.close()
    except Exception, e:
        print e
    if data is not None and len(data) == 4:
        a1 = (data[2][0], data[2][1])
        a2 = (data[3][0], data[3][1])
        if robot_id == 'ur':
            a1 = (data[2][1], data[2][0])
            a2 = (data[3][1], data[3][0])
        #rospy.logwarn(a1)
        #rospy.logwarn(a2)
        return _axis(data[0], data[1], a1, a2, point)
    else:
        #showwarning(title=None, message='标记点信息丢失,请重新标定！：')
        pub_command.publish("noMarkMsgError")





