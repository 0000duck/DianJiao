#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 17-12-7 下午5:08
# @Author  : yu
# @File    : my_dialog.py
# @Desc    :
from Tkinter import *
import tkSimpleDialog
from PIL import Image
from PIL import ImageTk
import tkFont
import cv2
from std_msgs.msg import String
# Ros 相关包
import rospy

class MyDialog(tkSimpleDialog.Dialog):

    def __init__(self, parent, title, type, img_ori):
        if type == 'board':
            self.tip = '注：图片中的棋盘不能横置，不要放置任何棋子'
            self.img_mark = parent.img_borad
        elif type == 'stone':
            self.tip = '请检查标定后的图像,如果每个棋子的文字有明显的破损,请调整摄像头,重新进行标定!'
            self.img_mark = parent.img_stone
        self.type = type
        self.img_ori = img_ori
        self.panel = NONE
        self.sub_command2 = rospy.Subscriber("judge2", String, self.callback)

        # get param
        self.robot_id = rospy.get_param('~robot_id')

        tkSimpleDialog.Dialog.__init__(self, parent.master, title)

    def body(self, master):
        image = Image.fromarray(self.img_mark)
        image = ImageTk.PhotoImage(image)

        self.panel = Label(master, image=image, text=self.tip, compound='top', font=('微软雅黑',15), fg='red')
        self.panel.image = image
	
        self.panel.pack(side="left", padx=10, pady=10)



    def apply(self):
        pass

    def buttonbox(self):
        box = Frame(self)
        w = Button(box, text="完成", width=10, command=self.finsh, default=ACTIVE)
        w.pack(side=LEFT, padx=5, pady=5)
        w = Button(box, text="取消", width=10, command=self.cancel)
        w.pack(side=LEFT, padx=5, pady=5)

        self.bind("<Return>", self.ok)
        self.bind("<Escape>", self.cancel)

        box.pack()

    def finsh(self):
        path = rospy.get_param('~path')
        cv2.imwrite(path+ self.robot_id + '_' + self.type+'.png', self.img_ori)
        print 'save scuccess!'
        self.ok()


    def callback(self,data):
        if data.data == 'stepFirstSecondSaveCommand':
            self.finsh()
        elif data.data == 'stepFirstSecondCancelCommand':
            self.cancel()




