#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 17-12-16 上午11:44
# @Author  : yu
# @File    : input_dialog.py
# @Desc    :
from Tkinter import *
import tkSimpleDialog
import pickle
import rospy, sys
import chess_look as cl
import cv2
import chess_msgs.srv
from sensor_msgs.msg import Image as Msg_Image
from cv_bridge import CvBridge, CvBridgeError
from tkMessageBox import *
from std_msgs.msg import String
import axis as ax

class InputDialog(tkSimpleDialog.Dialog):
    def __init__(self, parent, title):

        self.path = rospy.get_param('~path')
        self.robot_id = rospy.get_param('~robot_id')
        self.point_srv_name = rospy.get_param('~point_srv_name')
       
        self.bridge = CvBridge()
       
        self.subscriber = rospy.Subscriber("/usb_cam_node/image_rect_color",
                                           Msg_Image, self.img_callback)
        self.frame = None
        self.data = None
        self.e1 = None
        self.e2 = None
        self.e3 = None
        self.e4 = None
        self.e5 = None
        self.e6 = None
        self.e7 = None
        self.e8 = None

        self.str_e1 = StringVar()
        self.str_e2 = StringVar()
        self.str_e3 = StringVar()
        self.str_e4 = StringVar()

        self.str_e5 = StringVar()
        self.str_e6 = StringVar()
        self.str_e7 = StringVar()
        self.str_e8 = StringVar()
	self.pub_data = rospy.Publisher('locationData', String, queue_size=10)
	self.sub_command3 = rospy.Subscriber("judge3", String, self.callback)
        try:
            pkl_file = open(self.path + self.robot_id + '_' +'mark.txt', 'rb')
            data = pickle.load(pkl_file)
            self.data = data
            pkl_file.close()
        except Exception, e:
            print e
        tkSimpleDialog.Dialog.__init__(self, parent.master, title)

    
    def get_ur_point(self):
         rospy.wait_for_service(self.point_srv_name)#'ur_get_point'
         try:
            point = rospy.ServiceProxy(self.point_srv_name, chess_msgs.srv.Point)
            res = point()
            return res.x, res.y
         except rospy.ServiceException, e:
            rospy.logwarn('获取坐标 error')


    def body(self, master):

        Button(master, text="获取第一个点机器坐标(x,y):",command=self.get_point1).grid(row=0)
        Button(master, text="获取第一个点图像坐标(x,y):",command=self.get_point2).grid(row=1)
        Button(master, text="获取第二个点机器坐标(x,y):",command=self.get_point3).grid(row=2)
        Button(master, text="获取第二个点图像坐标(x,y):",command=self.get_point4).grid(row=3)

       

        self.e1 = Entry(master, textvariable=self.str_e1)
        self.e2 = Entry(master, textvariable=self.str_e2)
        self.e3 = Entry(master, textvariable=self.str_e3)
        self.e4 = Entry(master, textvariable=self.str_e4)

        self.e5 = Entry(master, textvariable=self.str_e5)
        self.e6 = Entry(master, textvariable=self.str_e6)
        self.e7 = Entry(master, textvariable=self.str_e7)
        self.e8 = Entry(master, textvariable=self.str_e8)

        if self.data is not None:
            self.str_e1.set(self.data[2][0])
            self.str_e2.set(self.data[2][1])
            self.str_e3.set(self.data[0][0])
            self.str_e4.set(self.data[0][1])
            self.str_e5.set(self.data[3][0])
            self.str_e6.set(self.data[3][1])
            self.str_e7.set(self.data[1][0])
            self.str_e8.set(self.data[1][1])

        self.e1.grid(row=0, column=1)
        self.e2.grid(row=0, column=2)
        self.e3.grid(row=1, column=1)
        self.e4.grid(row=1, column=2)

        self.e5.grid(row=2, column=1)
        self.e6.grid(row=2, column=2)

        self.e7.grid(row=3, column=1)
        self.e8.grid(row=3, column=2)

        return self.e1  # initial focus

    def buttonbox(self):
        box = Frame(self)
        w = Button(box, text="保存", width=10, command=self.finsh, default=ACTIVE)
        w.pack(side=LEFT, padx=5, pady=5)
        w = Button(box, text="取消", width=10, command=self.cancel)
        w.pack(side=LEFT, padx=5, pady=5)

        self.bind("<Return>", self.ok)
        self.bind("<Escape>", self.cancel)
        box.pack()

    def finsh(self):
        x1 = float(self.e3.get())
        y1 = float(self.e4.get())
        x2 = float(self.e7.get())
        y2 = float(self.e8.get())
        a1 = float(self.e1.get())
        a2 = float(self.e2.get())
        a3 = float(self.e5.get())
        a4 = float(self.e6.get())

        data1 = ((x1, y1), (x2, y2), (a1, a2), (a3, a4))
        output = open(self.path + self.robot_id + '_' +'mark.txt', 'wb')
        pickle.dump(data1, output)

        output.close()
        # self.subscriber = None
        # self.bridge = None
        self.ok()

    def get_point1(self):
        res = self.get_ur_point()
        if res is not None:
            self.str_e1.set(res[0])
            self.str_e2.set(res[1])
            self.pub_data.publish("a1"+self.e1.get())
            self.pub_data.publish("a2"+self.e2.get())

    def get_point3(self):
        res = self.get_ur_point()
        if res is not None:
            self.str_e5.set(res[0])
            self.str_e6.set(res[1])
            self.pub_data.publish("c1"+self.e5.get())
            self.pub_data.publish("c2"+self.e6.get())

    def get_point2(self):
        res = self.get_stone_xy()
        if res is not None:
            self.str_e3.set(res[0])
            self.str_e4.set(res[1])
            self.pub_data.publish("b1"+self.e3.get())
            self.pub_data.publish("b2"+self.e4.get())

    def get_point4(self):
        res = self.get_stone_xy()
        if res is not None:
            self.str_e7.set(res[0])
            self.str_e8.set(res[1])
            self.pub_data.publish("d1"+self.e7.get())
            self.pub_data.publish("d2"+self.e8.get())

  
    def img_callback(self, ros_data):
            try:
                self.frame = self.bridge.imgmsg_to_cv2(ros_data, "bgr8")
            except CvBridgeError as e:
                print(e)

    
    def get_stone_xy(self):
        self.pub_command = rospy.Publisher('judgeError', String, queue_size=1)
        rl, rn, bl, bn = cl.lookStone(self.frame)
        for index,name in enumerate(rn):
            if name == 'k':
               return rl[index][0]
        #showwarning(title=None, message='请确保棋盘存在红帅')
        self.pub_command.publish("noRedGeneralError")
        return None

    def callback(self,data):
        if data.data == 'getPointFirstLocCommand':
            self.get_point1()
        elif data.data == 'getStoneFirstLocCommand':
            self.get_point2()
        elif data.data == 'getPointSecondLocCommand':
            self.get_point3()
        elif data.data == 'getStoneSecondLocCommand':
            self.get_point4()	
        elif data.data == 'StepThirdSaveCommand':
	    self.finsh()			   
        elif data.data == 'StepThirdCancelCommand':
            self.cancel()	

