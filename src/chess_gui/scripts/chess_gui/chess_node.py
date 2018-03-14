#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 17-12-6 下午3:44
# @Author  : yu
# @File    : python main.py
# @Desc    :
import sys
import pickle
import time
from tkMessageBox import *
from ttk import *

import opencv.axis as ax
import opencv.chess_look as cl
import opencv.chess_move as cm
import opencv.chess_util as cu

from chess.chess import Chess
from chess_ui import *
from opencv.convenience import *
from opencv.input_dialog import InputDialog
from utils.my_dialog import MyDialog
from utils.xml_parse import xml_parse as xml_p
from skimage import morphology,draw
import numpy as np
import matplotlib.pyplot as plt

import threading

import rospy
import actionlib
import chess_msgs.msg
from std_msgs.msg import String
from sensor_msgs.msg import Image as Msg_Image
from cv_bridge import CvBridge, CvBridgeError
import time
import imutils
import cv2
from math import sqrt
COMMAND_RUN = False


price = {
   'R1': None,
   'R2': None,
   'N1': None,
   'N2': None,
   'B1': None,
   'B2': None,
   'A1': None,
   'A2': None,
   'K1': None,
   'C1': None,
   'C2': None,
   'P1': None,
   'P2': None,
   'P3': None,
   'P4': None,
   'P5': None,
   'r1': None,
   'r2': None,
   'n1': None,
   'n2': None,
   'b1': None,
   'b2': None,
   'a1': None,
   'a2': None,
   'k1': None,
   'c1': None,
   'c2': None,
   'p1': None,
   'p2': None,
   'p3': None,
   'p4': None,
   'p5': None,
}

class NumPonit:
	def __init__(self,temp):
		self.x = temp[0]     
		self.y = temp[1]
        



class chess_node(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        
        reload(sys)
        sys.setdefaultencoding('utf-8')

        self.master.title('点胶')
        self.master.config(bg='white')
       
        w, h = self.master.maxsize()
       
        self.master.geometry('{}x{}'.format(w/3+40, h/2+20))
        menu_bar = Menu(self.master)

        move_menu = Menu(menu_bar, tearoff=1)

        menu_bar.add_command(label="点", command=self.pTp)
        menu_bar.add_command(label="直线", command=self.lTl)
        menu_bar.add_command(label="弧线", command=self.people_go)
        menu_bar.add_command(label="面", command=self.plane)
        menu_bar.add_command(label="停止", command=self.stopbutton)
        #move_menu.add_command(label='开始', command=self.start_move_thread)
        #move_menu.add_command(label='停止', command=self.stop_move_thread)
        #menu_bar.add_cascade(label='摆棋', menu=move_menu)

        #voice_menu = Menu(menu_bar, tearoff=1)
        #voice_menu.add_command(label='开启', command=self.start_voice)
        #voice_menu.add_command(label='关闭', command=self.stop_voice)
        #menu_bar.add_cascade(label='语音', menu=voice_menu)

        self.master['menu'] = menu_bar
        
        self.server = None
       
        self.img_borad = None
        
        self.img_stone = None
        
        self.frame = None
        
        self.video_panel = None
       
        self.canvas = None
       
        # get param
        self.img_path = rospy.get_param('~path')
        self.robot_id = rospy.get_param('~robot_id')
        self.robot_name = rospy.get_param('~robot_name')
        self.chess_action_name = rospy.get_param('~chess_action_name')
        self.ai_ip = rospy.get_param('~ai_ip')
        self.ai_port = rospy.get_param('~ai_port')

        self.createWidgets()
        self.master.wm_protocol("WM_DELETE_WINDOW", self.onClose)
        
        self.bridge = CvBridge()
       
        self.subscriber = rospy.Subscriber("/usb_cam_node/image_rect_color",
                                           Msg_Image, self.img_callback)
        
        self.action_client = actionlib.SimpleActionClient(self.chess_action_name, chess_msgs.msg.StepAction)
       
        self.pub_voice = rospy.Publisher('speech_command', String, queue_size=1)
        self.send_voice_msg('start')
        
        self.sub_voice = rospy.Subscriber("speech_recognize", String, self.speech_callback)

       
        self.pub_command = rospy.Publisher('judgeError', String, queue_size=1)
        self.sub_command = rospy.Subscriber("judge", String, self.callback)

       
        self.move_chess = False
        self.chess_move_thread = threading.Thread(target=self.start_move)
        self.stop_chess_move_Event = threading.Event()
   
    def pointcmp(self,a,b,center0):
        #a = NumPonit(a)
        #b = NumPonit(b)
        if a.x >= 0 and b.x < 0:
            return True
        if a.x == 0 and b.x == 0:
            return a.y > b.y
        det =  (a.x - center0.x) * (b.y - center0.y) - (b.x - center0.x) * (a.y - center0.y)
        if det < 0:
            return True
        if det > 0:
            return False
        d1 = (a.x - center0.x) * (a.x - center0.x) + (a.y - center0.y) * (a.y - center0.y)
        d2 = (b.x - center0.x) * (b.x - center0.y) + (b.y - center0.y) * (b.y - center0.y)
        return d1 > d2

    def ClockwiseSortpoints(self,points):
        center0 = [0,0]
        center0 = NumPonit(center0)
        for tempcount in points:
            center0.x += tempcount.x
            center0.y += tempcount.y
        center0.x = center0.x / len(points)
        center0.y = center0.y / len(points)

        #pointcmp(points[0],points[1],center0)
        counti = 0
        while counti < len(points):
            countj = 0
            while countj < len(points) - counti -1:
                if self.pointcmp(points[countj],points[countj],center0):
                    tmp =  points[countj]
                    points[countj] = points[countj+1]
                    points[countj+1] = tmp;
                countj= countj + 1
            counti = counti + 1
    
    def centerpoint(self,points):
        center0 = [0,0]
        center0 = NumPonit(center0)
        for tempcount in points:
            center0.x += tempcount.x
            center0.y += tempcount.y
        center0.x = center0.x / len(points)
        center0.y = center0.y / len(points)
        return center0
   
    def centerpoint2(self,cnt):     
        M = cv2.moments(cnt)
        try:
	    cX = int(M["m10"] / M["m00"])
	    cY = int(M["m01"] / M["m00"])
       	    #x1,y1 = ax.axis((cX,cY))
            center0 = NumPonit([cX,cY])       
        except ZeroDivisionError:
            pass
        else:
            return center0
    


    def near_distance(self,a,points):
        distance = []
        for point in points:
            distance.append(round(self.get_distance(a,point), 2))
        temp1 = sorted(distance)

        indexnum = distance.index(temp1[0])
        return points[indexnum]

    
    def long_distance(self,a,points):
        distance = []
        for point in points:
            distance.append(round(self.get_distance(a,point), 2))
	with open("/home/carson/Desktop/temp/distance0.txt","w") as f:
            f.write(str(distance[0]))

        temp1 = sorted(distance)
	with open("/home/carson/Desktop/temp/distance1.txt","w") as f:
            f.write(str(distance[-1]))

        indexnum = distance.index(temp1[-1])
        return points[indexnum]
    
    def get_distance(self,a,b):
        return sqrt((a.x-b.x)**2 + (a.y-b.y)**2)
    

    '语音控制'
    def speech_callback(self, data):
       
        global COMMAND_RUN
      
        if COMMAND_RUN:
            return
        id = xml_p(data.data)
        if id == 1:
            COMMAND_RUN = True
            self.stop_voice()
            self.start_play()
            self.start_voice()
            COMMAND_RUN = False
        elif id == 11:
            COMMAND_RUN = True
            self.stop_voice()
            if self.people_go():
                self.robot_go()
            self.start_voice()
            COMMAND_RUN = False
        elif id == 12:
            COMMAND_RUN = True
            self.stop_voice()
            self.start_move_thread()
        elif id == 13:
            COMMAND_RUN = True
            self.stop_voice()
            self.stop_move_thread()
            self.start_voice()
            COMMAND_RUN = False
  
    def start_voice(self):
       
        self.send_voice_msg('on', 1)
    
    def stop_voice(self):
      
        self.send_voice_msg('off', 1)

   
    def img_callback(self, ros_data):
        try:
            self.frame = self.bridge.imgmsg_to_cv2(ros_data, "bgr8")
        except CvBridgeError as e:
            print(e)
        self.video_loop()

    def callback(self,data):
        if data.data == 'startPutChessCommand':
            self.start_move_thread()
        elif data.data == 'stopPutChessCommand':
            self.stop_move_thread()
	elif data.data == 'startVoiceChatCommand':
            self.start_voice()
	elif data.data == 'stopVoiceChatCommand':
            self.stop_voice()
	elif data.data == 'calibrationChessCommand1':
            self.mark_1()
	elif data.data == 'calibrationChessCommand2':
            self.mark_2()
	elif data.data == 'calibrationChessCommand3':
            self.mark_3()
	elif data.data == 'initChessCommand':
            self.start_play()
	elif data.data == 'playChessCommand':
            self.merge_move()	
        else:
            rospy.loginfo('test')
   
    def video_loop(self):
        try:
                image = resize(self.frame, width=650)
		time.sleep(0.05)
		cv2.imwrite('/var/www/html/assets/img/a.jpg', image)
                image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
                image = Image.fromarray(image)
                image = ImageTk.PhotoImage(image)
                if self.video_panel is None:
                    self.video_panel = Label(self.master, image=image, relief="solid", borderwidth=3)
                    self.video_panel.image = image
                    self.video_panel.pack(side=LEFT, padx=10)
                else:
                    self.video_panel.configure(image=image)
                    self.video_panel.image = image
        except RuntimeError, e:
            print("[INFO] caught a RuntimeError")

   
    def mark_1(self):
        img_ori = self.frame
        if img_ori is None:
            #showwarning(title=None, message='请先开启摄像头!')
            self.pub_command.publish("noCameraError")
            return
        try:
            self.img_borad = cl.markBoard(img_ori.copy())
            self.img_borad = resize(self.img_borad, 600)
            self.pub_command.publish("stepFirstConditionSuccess")
            #MyDialog(self, '标定结果', 'board', img_ori)
            
        except Exception, e:
            #showwarning(title=None, message='图片中的棋盘不能横置，不要放置任何棋子!')
            self.pub_command.publish("putChessError")
            print e
   
    def mark_2(self):
        img_ori = self.frame
        if img_ori is None:
            #showwarning(title=None, message='请先开启摄像头!')
            self.pub_command.publish("noCameraError")
            return
        if self.img_borad is not None:
                self.img_stone = cl.markStone(img_ori, 20)
                self.img_stone = resize(self.img_stone, 600)
                self.pub_command.publish("stepSecondConditionSuccess")
                #MyDialog(self, '标定结果', 'stone', img_ori)

        else:
            #showwarning(title=None, message='请先进行棋盘标定步骤1')
            self.pub_command.publish("noStepFirstError")
   
    def mark_3(self):
        self.check_mark()
        self.pub_command.publish("stepThirdConditionSuccess")
        #InputDialog(self, '录入坐标')

    def start_move_thread(self):
        if not self.check_action_connection:
            self.show_tip('与 ' + self.chess_action_name + ' 失去连接,请重启程序')
            return
        self.check_mark()
        self.send_voice_msg(self.robot_name + '收到2秒之后开始摆棋,请小心！')
       
        self.res_lookStone = cl.lookStone(self.frame)
        
        try:
           self.chess_move_thread.start()
        except Exception, e:
            print 'e'
        self.move_chess = True

    
    def stop_move_thread(self):
        self.move_chess = False
        self.send_voice_msg(self.robot_name + '收到停止摆棋,移动到等待位置')
       
        goal = chess_msgs.msg.StepGoal()
        self.generate_msg(goal,(0,0), (0,0), 2)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False

   
    def start_move(self):
        goal = chess_msgs.msg.StepGoal()
        try:
            while not self.stop_chess_move_Event.is_set():
              
                while True:
                    if not self.move_chess:
                        break
                    rl, rn, bl, bn = self.res_lookStone
                    res = cm.moveStone(rl, rn, bl, bn)
                    rospy.logwarn(res)
                    if res is None:
                       
                        self.send_voice_msg(self.robot_name + '摆棋完成 移动到等待位置')
                        self.generate_msg(goal, (0,0), (0,0), 2)
                        self.send_msg(goal)
                        goal.ops = []
                        self.start_voice()
                        global COMMAND_RUN
                        COMMAND_RUN = False
                        self.move_chess = False
                        break
                    
                    if res[1]:
                        self.send_voice_msg('移动红方'+cl.get_chess_name(rn[res[0]]))
                    else:
                        if cl.get_chess_name(bn[res[0]]) == '帅':
                            name = '将'
                        elif cl.get_chess_name(bn[res[0]]) == '兵':
                            name = '卒'
                        else:
                            name = cl.get_chess_name(bn[res[0]])
                        self.send_voice_msg('移动黑方' + name)
                    # =============================
                    img_1 = cl.mergeStone(rl, bl, rn, bn)
                    cv2.line(img_1, res[2], res[3], 255, 1)
                    img_1 = resize(img_1, width=800)
                    cv2.imshow('move_step,', img_1)
                    # =============================
                    self.generate_msg(goal, res[2], res[3], 0)
                    if cv2.waitKey(1000) & 0xFF == ord('q'):
                        break
                    if self.send_msg(goal):
                        goal.ops = []
                        continue
                    else:
                        self.stop_move_thread()
                        break
                cv2.destroyAllWindows()
        except Exception, e:
            rospy.logwarn(e)
            rospy.logwarn('摆棋出现错误')

   
    def generate_msg(self, goal, pick, place, type):
        op = chess_msgs.msg.Operation()
        op.type = type
        op.pick_x, op.pick_y = ax.axis(pick)
        op.place_x, op.place_y = ax.axis(place)
        if self.robot_id == 'ur':
            op.pick_y, op.pick_x = ax.axis(pick)
            op.place_y, op.place_x = ax.axis(place)

        # far = 0; near = 1
        if cl.xy2Grid(pick)[1] > 4:
            op.pick_type = 1
        else:
            op.pick_type = 0

        if cl.xy2Grid(place)[1] > 4:
            op.place_type = 1
        else:
            op.place_type = 0

        #op.pick_type = 1
        #op.place_type = 1
        goal.ops.append(op)
        # Sends the goal to the action server.
        rospy.logwarn('----------------')
        rospy.logwarn(pick)
        rospy.logwarn(place)
        rospy.logwarn(goal)
        rospy.logwarn('----------------')
        return goal

   
    def send_msg(self, goal):
        self.action_client.send_goal(goal)
       
        result = self.action_client.wait_for_result(rospy.Duration(60, 0))
        if result:
            result_data = self.action_client.get_result()
            if result_data.res:
                self.show_tip('移动成功')
            else:
                self.show_tip('移动失败')
            return True
        else:
            if not self.check_action_connection:
                self.show_tip('与 ' + self.chess_action_name + ' 失去连接,请重启')
                return False
            else:
                self.show_tip('移动棋子超时')
                return True

   
    def check_action_connection(self):
        return self.action_client.wait_for_server(rospy.Duration(1, 0))

   
    def update_price(self):
        update_price_coordinates(self.canvas, price)

  
    def start_play(self):
        self.check_mark()
        rl, rn, bl, bn = cl.lookStone(self.frame)
        board, red_up = cl.stone2Board(rl, rn, bl, bn)
        board = self.strBoard(board)
       
        if self.server is None:
            self.server = Chess(self.ai_ip, self.ai_port)
        res = self.server.startBoard(
            board, not red_up)
        if not (res is None):
            s = u'初始化错误：' + res
            self.show_tip(s)
        else:
           
            self.structure_price_coordinates(rl, rn, bl, bn)
            self.send_voice_msg('初始化完毕,可以开始下棋了')

    def merge_move(self):
        if self.people_go():
                self.robot_go()
    def robot_go(self):
        if self.server is None:
            self.show_tip('请先点击开始下棋或者发送开始下棋命令！')
            return
        self.send_voice_msg('轮到' + self.robot_name + '下棋了请您离' + self.robot_name + '远一点！')
       
        rl, rn, bl, bn = cl.lookStone(self.frame)
        res = self.server.thinkAndMove(False)
       
        goal = chess_msgs.msg.StepGoal()
        if res:
            pick, place = self.coordinate_trans(res[2:])
            has = cl.hasStone(rl, rn, bl, bn, place)
            if has is None:
               
                move_price(self.canvas, pick, place)
               
                place = cl.grid2XY(place)
                h1, h2, h3 = cl.hasStone(rl, rn, bl, bn, pick)
                self.send_voice_msg('走'+cl.get_chess_name(h2,h3))
                goal = self.generate_msg(goal, h1[0], place, 0)
                self.send_msg(goal)
                goal.ops = []
               
                self.send_voice_msg('移动' + self.robot_name + '到等待位置')
                self.generate_msg(goal, pick, place, 2)
                self.send_msg(goal)
            else:
               
                capture_price(self.canvas, place)
                move_price(self.canvas, pick, place)
               
                h1,h2,h3 = cl.hasStone(rl, rn, bl, bn, place)
                self.send_voice_msg('吃' + cl.get_chess_name(h2,h3))
                goal = self.generate_msg(goal, h1[0], pick, 1)
                self.send_msg(goal)
                goal.ops = []

               
                h1, h2, h3 = cl.hasStone(rl, rn, bl, bn, pick)
                self.send_voice_msg('走' + cl.get_chess_name(h2,h3))
                place = cl.grid2XY(place)
                goal = self.generate_msg(goal, h1[0], place, 0)
                self.send_msg(goal)
               
                self.send_voice_msg('移动' + self.robot_name + '到等待位置')
                goal.ops = []
                self.generate_msg(goal, pick, place, 2)
                self.send_msg(goal)
        else:
            self.send_voice_msg('这已经没什么可走的了！')
    def pTp(self):
        image = self.frame
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	cv2.imwrite('/home/carson/Desktop/temp/c.png', gray)
        _,thresh = cv2.threshold(gray, 110, 255, cv2.THRESH_BINARY_INV)
	cv2.imwrite('/home/carson/Desktop/temp/b.png',thresh )
        cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if imutils.is_cv2() else cnts[1]
        points=[]

	for c in cnts:
	    # compute the center of the contour
	    M = cv2.moments(c)
            print(M["m00"])
            try:
	        cX = int(M["m10"] / M["m00"])
	        cY = int(M["m01"] / M["m00"])
		#x1,y1 = ax.axis((cX,cY))
                points.append(NumPonit([cX,cY]))
               
            except ZeroDivisionError:
                pass
            else:
	        # draw the contour and center of the shape on the image
	        cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
	        cv2.circle(image, (cX, cY), 7, (255, 255, 255), -1)
	   
	        cv2.putText(image, "center", (cX - 20, cY - 20),
	        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
 
	        # show the image
	        cv2.imwrite('/home/carson/Desktop/temp/a.png',image)
        
	self.ClockwiseSortpoints(points)
        points.append(points[0])
        with open("/home/carson/Desktop/temp/douban3.txt","w") as f:
                    f.write(str(points[0].x)+"a")
        self.move_chess = False
	self.send_voice_msg(self.robot_name + '收到2秒之后开始点胶,请小心！')
       
        countnum = 0
        while countnum < len(points) - 1:
            op = chess_msgs.msg.Operation()
            op.type = 0
            goal = chess_msgs.msg.StepGoal()
	    temp = points[countnum]
            op.pick_x,op.pick_y = ax.axis((temp.x,temp.y))
	    temp = points[countnum+1]
            op.place_x, op.place_y=ax.axis((temp.x,temp.y))
            
            goal.ops.append(op)
            #self.generate_msg(goal,(300,300), (500,300), 0)
            self.send_msg(goal)
            goal.ops = []
            countnum = countnum + 1
            #self.start_voice()
            
 	self.send_voice_msg(self.robot_name + '点胶完成,移动到等待位置')
        op = chess_msgs.msg.Operation()
        op.type = 2
        goal = chess_msgs.msg.StepGoal()
        goal.ops.append(op)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False

    def lTl(self):
        image = self.frame
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	cv2.imwrite('/home/carson/Desktop/temp/c.png', gray)
        _,thresh = cv2.threshold(gray, 110, 255, cv2.THRESH_BINARY_INV)
        cv2.normalize(thresh,thresh,0,1,cv2.NORM_MINMAX)
        skeleton =morphology.skeletonize(thresh)

        number = 0
        points=[]
        test = np.zeros((1080, 1280))
        for i in range(skeleton.shape[0]):
            for j in range(skeleton.shape[1]):
	        if skeleton[i,j] == 1:
                    #number = number + 1
                    #if number % 30 == 0 or number == 1:
                    test[i,j] = skeleton[i,j] * 255
                    points.append(NumPonit([j,i]))
                
        cv2.imwrite('/home/carson/Desktop/temp/test.png', test)
        
	#self.ClockwiseSortpoints(points)
        #points.append(points[0])


        newpoints = []
        newpoints.append(NumPonit([points[0].x,points[0].y]))
        newpoints.append(NumPonit([points[-1].x,points[-1].y]))

      

        with open("/home/carson/Desktop/temp/douban3.txt","w") as f:
            f.write(" "+str(number)+" ")
        self.move_chess = False
	self.send_voice_msg(self.robot_name + '收到2秒之后开始点胶,请小心！')
       
        countnum = 0
        while countnum < len(newpoints) - 1:
            op = chess_msgs.msg.Operation()
            op.type = 0
            goal = chess_msgs.msg.StepGoal()
	    temp = newpoints[countnum]
            op.pick_x,op.pick_y = ax.axis((temp.x,temp.y))
	    temp = newpoints[countnum+1]
            op.place_x, op.place_y=ax.axis((temp.x,temp.y))
            
            goal.ops.append(op)
            #self.generate_msg(goal,(300,300), (500,300), 0)
            self.send_msg(goal)
            goal.ops = []
            countnum = countnum + 1
            #self.start_voice()
            
 	self.send_voice_msg(self.robot_name + '点胶完成,移动到等待位置')
        op = chess_msgs.msg.Operation()
        op.type = 2
        goal = chess_msgs.msg.StepGoal()
        goal.ops.append(op)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False

    def people_go(self):

        image = self.frame
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	cv2.imwrite('/home/carson/Desktop/c.png', gray)
        _,thresh = cv2.threshold(gray, 110, 255, cv2.THRESH_BINARY_INV)
        #centerpoint1 = self.centerpoint2(thresh)
        cv2.normalize(thresh,thresh,0,1,cv2.NORM_MINMAX)
        skeleton =morphology.skeletonize(thresh)

        number = 0
        points=[]
        test = np.zeros((1080, 1280))
        for i in range(skeleton.shape[0]):
            for j in range(skeleton.shape[1]):
	        if skeleton[i,j] == 1:
                    #number = number + 1
                    #if number % 30 == 0 or number == 1:
                    test[i,j] = skeleton[i,j] * 255
                    points.append(NumPonit([j,i]))
                
        cv2.imwrite('/home/carson/Desktop/test.png', test)
        


        '''
        cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if imutils.is_cv2() else cnts[1]
	for c in cnts:
	    # compute the center of the contour
	    M = cv2.moments(c)
            print(M["m00"])
            try:
	        cX = int(M["m10"] / M["m00"])
	        cY = int(M["m01"] / M["m00"])
		#x1,y1 = ax.axis((cX,cY))
                points.append(NumPonit([cX,cY]))
               
            except ZeroDivisionError:
                pass
            else:
	        # draw the contour and center of the shape on the image
	        cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
	        cv2.circle(image, (cX, cY), 7, (255, 255, 255), -1)
	   
	        cv2.putText(image, "center", (cX - 20, cY - 20),
	        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)
 
	        # show the image
	        cv2.imwrite('/home/carson/Desktop/a.png',image)
            '''
	self.ClockwiseSortpoints(points)
        #points.append(points[0])


        newpoints = []
        i = 0
        while i < len(points):
            if i % 20 == 0 or i == len(points) - 1 or i == 0:
                newpoints.append(NumPonit([points[i].x,points[i].y]))
            i = i + 1  

        self.ClockwiseSortpoints(newpoints)


        centerpoint1 = self.centerpoint(newpoints)
        with open("/home/carson/Desktop/temp/centerpoint1.txt","w") as f:
            f.write(" "+str(centerpoint1.x)+" "+" "+str(centerpoint1.y)+" ")
        longpoint = self.long_distance(centerpoint1,newpoints)
        with open("/home/carson/Desktop/temp/longpoint.txt","w") as f:
            f.write(" "+str(longpoint)+" ")
        
        
	lastpointlist = []
	firstpoint = newpoints.index(longpoint)
	firstpoint = newpoints.pop(firstpoint)
        lastpointlist.append(firstpoint)
        while newpoints:
            secondpoint = self.near_distance(firstpoint,newpoints)
            lastpointlist.append(secondpoint)
            firstpoint = newpoints.pop(newpoints.index(secondpoint))
        

        




        with open("/home/carson/Desktop/temp/douban3.txt","w") as f:
            f.write(" "+str(number)+" ")
        self.move_chess = False
	self.send_voice_msg(self.robot_name + '收到2秒之后开始点胶,请小心！')
       
        countnum = 0
        while countnum < len(lastpointlist) - 1:
            op = chess_msgs.msg.Operation()
            op.type = 0
            goal = chess_msgs.msg.StepGoal()
	    temp = lastpointlist[countnum]
            op.pick_x,op.pick_y = ax.axis((temp.x,temp.y))
	    temp = lastpointlist[countnum+1]
            op.place_x, op.place_y=ax.axis((temp.x,temp.y))
            
            goal.ops.append(op)
            #self.generate_msg(goal,(300,300), (500,300), 0)
            self.send_msg(goal)
            goal.ops = []
            countnum = countnum + 1
            #self.start_voice()


 	self.send_voice_msg(self.robot_name + '点胶完成,移动到等待位置')
        op = chess_msgs.msg.Operation()
        op.type = 2
        goal = chess_msgs.msg.StepGoal()
        goal.ops.append(op)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False


        
    def plane(self):
        
        image = self.frame
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	cv2.imwrite('/home/carson/Desktop/c.png', gray)
        _,thresh = cv2.threshold(gray, 110, 255, cv2.THRESH_BINARY_INV)
        #centerpoint1 = self.centerpoint2(thresh)
        cv2.normalize(thresh,thresh,0,1,cv2.NORM_MINMAX)
        skeleton =morphology.skeletonize(thresh)

        number = 0
        points=[]
        test = np.zeros((1080, 1280))
        for i in range(skeleton.shape[0]):
            for j in range(skeleton.shape[1]):
	        if skeleton[i,j] == 1:
                    #number = number + 1
                    #if number % 30 == 0 or number == 1:
                    test[i,j] = skeleton[i,j] * 255
                    points.append(NumPonit([j,i]))
                
        cv2.imwrite('/home/carson/Desktop/test.png', test)
        

	self.ClockwiseSortpoints(points)
        #points.append(points[0])


        newpoints = []
        i = 0
        while i < len(points):
            if i % 20 == 0 or i == len(points) - 1 or i == 0:
                newpoints.append(NumPonit([points[i].x,points[i].y]))
            i = i + 1  

        self.ClockwiseSortpoints(newpoints)


        points1=[]
        test2 = np.zeros((1080, 1280))
        for kkk in newpoints:
             test2[kkk.y,kkk.x] = 255
            
        cv2.imwrite('/home/carson/Desktop/test0.png', test2)














        
        centerpoint1 = self.centerpoint(newpoints)
        with open("/home/carson/Desktop/temp/centerpoint1.txt","w") as f:
            f.write(" "+str(centerpoint1.x)+" "+" "+str(centerpoint1.y)+" ")
        longpoint = self.long_distance(centerpoint1,newpoints)
        with open("/home/carson/Desktop/temp/longpoint.txt","w") as f:
            f.write(" "+str(longpoint)+" ")
        
        newpointscopy = newpoints[:]
	lastpointlist0 = []
	firstpoint = newpointscopy.index(longpoint)
	firstpoint = newpointscopy.pop(firstpoint)
        lastpointlist0.append(firstpoint)
        while newpointscopy:
            secondpoint = self.near_distance(firstpoint,newpointscopy)
            lastpointlist0.append(secondpoint)
            firstpoint = newpointscopy.pop(newpointscopy.index(secondpoint))
        

        




        



























        #centerpoint1 = self.centerpoint(newpoints)
        with open("/home/carson/Desktop/temp/centerpoint1.txt","w") as f:
            f.write(" "+str(centerpoint1.x)+" "+" "+str(centerpoint1.y)+" ")


        nearpoint = self.near_distance(centerpoint1,newpoints)
        with open("/home/carson/Desktop/temp/longpoint.txt","w") as f:
            f.write(" "+str(nearpoint)+" ")
        
        neardistance = self.get_distance(nearpoint,centerpoint1)
        r = neardistance / 2
        leftpoint = centerpoint1.x - r
        rightpoint = centerpoint1.x + r

        xlist = []
       
        i = 0
        blocks = 6
        addnum = (2 * r) / blocks
        while i < blocks:
            temp0 = leftpoint + addnum * i
            xlist.append(temp0)
            i = i + 1

        xlist.append(rightpoint)    

        with open("/home/carson/Desktop/temp/xlist.txt","w") as f:
            f.write(str(xlist[0])+" "+str(xlist[1])+" "+str(xlist[2])+" "+str(xlist[3])+" "+str(xlist[4])+" "+str(xlist[5])+" "+str(xlist[6])+" ")


        heightlist = []
        heightlist.append(0)
        i = 1
        while i < blocks:
            heightnum = sqrt(r**2 - (xlist[i] - centerpoint1.x)**2) + centerpoint1.y
            heightnum = abs(centerpoint1.y -heightnum) 
            heightlist.append(heightnum)
            i = i + 1
        heightlist.append(0)

        with open("/home/carson/Desktop/temp/heightlist.txt","w") as f:
            f.write(str(heightlist[0])+" "+str(heightlist[1])+" "+str(heightlist[2])+" "+str(heightlist[3])+" "+str(heightlist[4])+" "+str(heightlist[5])+" "+str(heightlist[6])+" ")



        lastpointlist = []
        ylist = []
        i = 0
        while i <= blocks:
            ylist.append(int(centerpoint1.y - heightlist[i]))
            lastpointlist.append(NumPonit([int(xlist[i]),int(ylist[i])]))
            i = i + 1


        i = 1
        xlist.reverse()
        heightlist.reverse()
        while i < blocks:
            ylist[i] = (centerpoint1.y + heightlist[i])
            lastpointlist.append(NumPonit([int(xlist[i]),int(ylist[i])]))
            i = i + 1
        lastpointlist.append(lastpointlist[0]) 


        with open("/home/carson/Desktop/temp/lastpointlist.txt","w") as f:
            f.write(str(len(lastpointlist)))



      

        
        lastpointlist = lastpointlist0 + lastpointlist

        points1=[]
        test1 = np.zeros((1080, 1280))
        for kkk in lastpointlist:
             test1[kkk.y,kkk.x] = 255
            
        cv2.imwrite('/home/carson/Desktop/test1.png', test1)

        with open("/home/carson/Desktop/temp/douban3.txt","w") as f:
            f.write(" "+str(number)+" ")
        self.move_chess = False
	self.send_voice_msg(self.robot_name + '收到2秒之后开始点胶,请小心！')
       
        countnum = 0
        while countnum < len(lastpointlist) - 1:
            op = chess_msgs.msg.Operation()
            op.type = 0
            goal = chess_msgs.msg.StepGoal()
	    temp = lastpointlist[countnum]
            op.pick_x,op.pick_y = ax.axis((temp.x,temp.y))
	    temp = lastpointlist[countnum+1]
            op.place_x, op.place_y=ax.axis((temp.x,temp.y))
            
            goal.ops.append(op)
            #self.generate_msg(goal,(300,300), (500,300), 0)
            self.send_msg(goal)
            goal.ops = []
            countnum = countnum + 1
            #self.start_voice()


 	self.send_voice_msg(self.robot_name + '点胶完成,移动到等待位置')
        op = chess_msgs.msg.Operation()
        op.type = 2
        goal = chess_msgs.msg.StepGoal()
        goal.ops.append(op)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False

        
        








        '''        
        image = self.frame
        image1 = image




        gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)   
        ret,thresh = cv2.threshold(gray,110,255,cv2.THRESH_BINARY_INV)
  	cv2.imwrite('/home/carson/Desktop/temp/b.png',thresh )
        image, contours, hierarchy = cv2.findContours(thresh,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE) 
        pentagram= contours[1]


        inflectionpoint0 = tuple(pentagram[:,0][0])  
        inflectionpoint1 = tuple(pentagram[:,0][2]) 
        inflectionpoint2 = tuple(pentagram[:,0][4]) 
        inflectionpoint3 = tuple(pentagram[:,0][6])


        cv2.circle(image1, inflectionpoint0, 2, (255,255,255),3) 
        cv2.circle(image1, inflectionpoint1, 2, (255,0,0),3) 
        cv2.circle(image1, inflectionpoint2, 2, (0,255,0),3) 

        #cv2.circle(image1, inflectionpoint0, 2, (0,255,0),3)
           
        #cv2.imshow('img',image1) 
        cv2.imwrite('/home/carson/Desktop/temp/qqq.png',image1 )

        temp01 = [(inflectionpoint0[0] + inflectionpoint1[0])/2 , (inflectionpoint0[1] + inflectionpoint1[1])/2 ]
        temp12 = [(inflectionpoint1[0] + inflectionpoint2[0])/2 , (inflectionpoint1[1] + inflectionpoint2[1])/2 ]
        temp23 = [(inflectionpoint2[0] + inflectionpoint3[0])/2 , (inflectionpoint2[1] + inflectionpoint3[1])/2 ]
        temp30 = [(inflectionpoint3[0] + inflectionpoint0[0])/2 , (inflectionpoint3[1] + inflectionpoint0[1])/2 ]

        narrowpoint0 = ((temp01[0] + temp30[0])/2 , (temp01[1] + temp30[1])/2 )
        narrowpoint1 = ((temp01[0] + temp12[0])/2 , (temp01[1] + temp12[1])/2 )
        narrowpoint2 = ((temp12[0] + temp23[0])/2 , (temp12[1] + temp23[1])/2 )
        narrowpoint3 = ((temp23[0] + temp30[0])/2 , (temp23[1] + temp30[1])/2 )


        points=[]
        points.append(NumPonit([inflectionpoint0[0],inflectionpoint0[1]]))
        points.append(NumPonit([inflectionpoint1[0],inflectionpoint1[1]]))
        points.append(NumPonit([inflectionpoint2[0],inflectionpoint2[1]]))
        points.append(NumPonit([inflectionpoint3[0],inflectionpoint3[1]]))

        points.append(points[0])
        with open("/home/carson/Desktop/temp/www.txt","w") as f:
            f.write(str(inflectionpoint0[0])+" "+str(inflectionpoint0[1]))
              
        self.move_chess = False
	self.send_voice_msg(self.robot_name + '收到2秒之后开始点胶,请小心！')
       
        countnum = 0
        while countnum < len(points) - 1:
            op = chess_msgs.msg.Operation()
            op.type = 0
            goal = chess_msgs.msg.StepGoal()
	    temp = points[countnum]
            op.pick_x,op.pick_y = ax.axis((temp.x,temp.y))
	    temp = points[countnum+1]
            op.place_x, op.place_y=ax.axis((temp.x,temp.y))
            
            goal.ops.append(op)
            #self.generate_msg(goal,(300,300), (500,300), 0)
            self.send_msg(goal)
            goal.ops = []
            countnum = countnum + 1
            #self.start_voice()
            
        newpoints=[]
        newpoints.append(NumPonit([narrowpoint0[0],narrowpoint0[1]]))
        newpoints.append(NumPonit([narrowpoint1[0],narrowpoint1[1]]))
        newpoints.append(NumPonit([narrowpoint2[0],narrowpoint2[1]]))
        newpoints.append(NumPonit([narrowpoint3[0],narrowpoint3[1]]))

        newpoints.append(newpoints[0])
        with open("/home/carson/Desktop/temp/douban3.txt","w") as f:
                    f.write(str(newpoints[0].x)+"a")
        self.move_chess = False
	self.send_voice_msg(self.robot_name + '收到2秒之后开始点胶,请小心！')
       
        countnum = 0
        while countnum < len(newpoints) - 1:
            op = chess_msgs.msg.Operation()
            op.type = 0
            goal = chess_msgs.msg.StepGoal()
	    temp = newpoints[countnum]
            op.pick_x,op.pick_y = ax.axis((temp.x,temp.y))
	    temp = newpoints[countnum+1]
            op.place_x, op.place_y=ax.axis((temp.x,temp.y))
            
            goal.ops.append(op)
            #self.generate_msg(goal,(300,300), (500,300), 0)
            self.send_msg(goal)
            goal.ops = []
            countnum = countnum + 1
            #self.start_voice()
            







 	self.send_voice_msg(self.robot_name + '点胶完成,移动到等待位置')
        op = chess_msgs.msg.Operation()
        op.type = 2
        goal = chess_msgs.msg.StepGoal()
        goal.ops.append(op)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False

        
    
        '''

    def stopbutton(self):
 
        self.move_chess = False
 	self.send_voice_msg(self.robot_name + '点胶完成,移动到等待位置')
        op = chess_msgs.msg.Operation()
        op.type = 2
        goal = chess_msgs.msg.StepGoal()
        goal.ops.append(op)
        self.send_msg(goal)
        goal.ops = []
        self.start_voice()
        global COMMAND_RUN
        COMMAND_RUN = False


    def check_mark(self):
        if self.frame is None:
            #showwarning(title=None, message="请先开启摄像头！")
            self.pub_command.publish("noCameraError")
            return
        if self.img_borad is None:
            img_borad = cv2.imread(self.img_path + self.robot_id + '_' + 'board.png', cv2.IMREAD_COLOR)
            if img_borad is not None:
                self.img_borad = cl.markBoard(img_borad.copy())
            else:
                #showwarning(title=None, message="请先进行标定步骤一！")
                self.pub_command.publish("noStepFirstError")
                return

        if self.img_stone is None:
            img_stone = cv2.imread(self.img_path + self.robot_id + '_' + 'stone.png', cv2.IMREAD_COLOR)
            if img_stone is not None:
                self.img_stone = cl.markStone(img_stone.copy(),20)
            else:
                #showwarning(title=None, message="请先进行标定步骤二！")
                self.pub_command.publish("noStepSecondError")
                return
        data = None
        try:
            pkl_file = open(self.img_path + self.robot_id + '_' + 'mark.txt', 'rb')
            data = pickle.load(pkl_file)
            pkl_file.close()
        except Exception, e:
            print e
        if data is None:
            #showwarning(title=None, message="请先进行标定步骤三！")
            return

    def createWidgets(self):
       
        #self.canvas = draw_chess(self.master)
        button_panel = Frame(self.master, width=40, height=800,bg='white')
        #Button(button_panel, text='开始下棋', command=self.start_play).pack(pady=10)
        #Button(button_panel, text=self.robot_name + '下棋', command=self.merge_move).pack(pady=10)
        #Button(button_panel, text='点对点', command=self.pTp).pack(pady=10)
        #Button(button_panel, text='直线', command=self.lTl).pack(pady=10)
        #Button(button_panel, text='弧线', command=self.people_go).pack(pady=10)
        
        #button_panel.pack(side=LEFT, padx=10)

   
    def strBoard(self, board):
        one = ''
        two = ''
        for x in xrange(len(board)):
            if x < cu.Rows / 2:
                one = one + ''.join(board[x]) + '/ '
            else:
                two = two + ''.join(board[x]) + '/ '
        return (one + two).replace(' ', '')

    def structure_price_coordinates(self, rl, rn, bl, bn):
        price_coordinates=price
        p=0
        c=0
        r=0
        n=0
        b=0
        a=0
        for i,v in enumerate(rl):
            key = str(rn[i]).upper()
            if key == 'K':
                price_coordinates['K1'] = cl.xy2Grid(v[0])
            elif key == 'P':
                price_coordinates[key+str(p+1)] = cl.xy2Grid(v[0])
                p = p+1
            elif key == 'C':
                price_coordinates[key + str(c+1)] = cl.xy2Grid(v[0])
                c = c + 1
            elif key == 'R':
                price_coordinates[key + str(r + 1)] = cl.xy2Grid(v[0])
                r = r + 1
            elif key == 'N':
                price_coordinates[key + str(n + 1)] = cl.xy2Grid(v[0])
                n = n + 1
            elif key == 'B':
                price_coordinates[key + str(b + 1)] = cl.xy2Grid(v[0])
                b = b + 1
            elif key == 'A':
                price_coordinates[key + str(a + 1)] = cl.xy2Grid(v[0])
                a = a + 1

        p = 0
        c = 0
        r = 0
        n = 0
        b = 0
        a = 0
        for i, v in enumerate(bl):
            key = str(bn[i])
            if key == 'k':
                price_coordinates['k1'] = cl.xy2Grid(v[0])
            elif key == 'p':
                price_coordinates[key + str(p + 1)] = cl.xy2Grid(v[0])
                p = p + 1
            elif key == 'c':
                price_coordinates[key + str(c + 1)] = cl.xy2Grid(v[0])
                c = c + 1
            elif key == 'r':
                price_coordinates[key + str(r + 1)] = cl.xy2Grid(v[0])
                r = r + 1
            elif key == 'n':
                price_coordinates[key + str(n + 1)] = cl.xy2Grid(v[0])
                n = n + 1
            elif key == 'b':
                price_coordinates[key + str(b + 1)] = cl.xy2Grid(v[0])
                b = b + 1
            elif key == 'a':
                price_coordinates[key + str(a + 1)] = cl.xy2Grid(v[0])
                a = a + 1
        update_price_coordinates(self.canvas,price_coordinates)
   
    def coordinate_trans(self, move):
        if move and len(move) != 4:
            print '移动出错'
        a1 = (self.to_letter(move[0]), 9-int(move[1]))
        a2 = (self.to_letter(move[2]), 9 - int(move[3]))
        return a1, a2

    def to_letter(self, s):
        if s == 'a':
            s = 0
        elif s == 'b':
            s = 1
        elif s == 'c':
            s = 2
        elif s == 'd':
            s = 3
        elif s == 'e':
            s = 4
        elif s == 'f':
            s = 5
        elif s == 'g':
            s = 6
        elif s == 'h':
            s = 7
        elif s == 'i':
            s = 8
        return s

    def send_voice_msg(self, message, flag=0):
        if flag == 0:
            msg = "talk " + message
        elif flag == 1:
            msg = "listen " + message
        if not rospy.is_shutdown():
            self.pub_voice.publish(msg)

   
    def show_tip(self, message):
        self.send_voice_msg(message)
       

    
    def onClose(self):
        print("[INFO] closing...")
        try:
            self.bridge = None
            self.server = None
            self.canvas = None
            self.action_client = None
            self.pub_voice = None
            self.subscriber = None
            self.stop_chess_move_Event.set()
        except Exception,e:
            rospy.logwarn('closing')
        # Shutdown
        rospy.signal_shutdown("Done.")
        self.master.quit()



if __name__ == "__main__":
    try:
       
        rospy.init_node('chess_node')
        app = chess_node()
        app.mainloop()

    except rospy.ROSInterruptException:
        print "program interrupted before completion"
