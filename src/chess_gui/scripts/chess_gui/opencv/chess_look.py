#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import numpy as np
import rospy
import chess_util as cu
from tkMessageBox import *
from std_msgs.msg import String
def markBoard(bgr):
    cu.Height, cu.Width = bgr.shape[:2]

    (cu.MinX, cu.MinY), (cu.MaxX, cu.MaxY) = cu.filterBoard(bgr)

    cu.SepX = float((cu.MaxX - cu.MinX)) / (cu.Cols - 1)
    cu.SepY = float((cu.MaxY - cu.MinY)) / (cu.Rows - 1)

    for r in xrange(cu.Rows):
        for c in xrange(cu.Cols):
            x, y = grid2XY((c, r))
            cv2.line(bgr, (x - 5, y), (x + 5, y), (0, 0, 255), 2)
            cv2.line(bgr, (x, y - 5), (x, y + 5), (0, 0, 255), 2)
    img_path = rospy.get_param('~path')
    cv2.imwrite('/var/www/html/assets/img/b.png', bgr)
    bgr = cv2.cvtColor(bgr, cv2.COLOR_BGR2RGB)
    return bgr

def markStone(bgr, num=20):
    pub_command = rospy.Publisher('judgeError', String, queue_size=1)
    cu.MinRadius = int(cu.Width / num / 2)

    cu.RedList, cu.BlackList = cu.filterStone(bgr)
    if len(cu.RedList) != 16:
        #show_info(u'红棋的数量应该为16个')
        pub_command.publish("noRedNumError")
        raise Exception(u'红棋的数量应该为16个')
    if len(cu.BlackList) != 16:
        #show_info(u'黑棋的数量应该为16个')
        pub_command.publish("noBlackNumError")
        raise Exception(u'黑棋的数量应该为16个')

    
    radius = [one[1].shape[0] for one in cu.RedList]
    radius.extend([one[1].shape[0] for one in cu.BlackList])
    cu.MaxRadius = (max(radius) - 1) / 2

    cu.RedName = ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1']
    cu.BlackName = ['1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1']

    
    grid = [xy2Grid(one[0]) for one in cu.RedList]
    for n in xrange(len(grid)):
        x, y = grid[n]
        if cu.Board[y][x] == '1':
            #show_info(u'红色棋子位置不对')
            pub_command.publish("noRedLocationError")
            raise Exception(u'红色棋子位置不对')
        cu.RedName[n] = cu.Board[y][x]
    grid = [xy2Grid(one[0]) for one in cu.BlackList]
    for n in xrange(len(grid)):
        x, y = grid[n]
        if cu.Board[y][x] == '1':
            #show_info(u'黑色棋子位置不对')
            pub_command.publish("noBlackLocationError")
            raise Exception(u'黑色棋子位置不对')
        cu.BlackName[n] = cu.Board[y][x]

    return mergeStone(cu.RedList, cu.BlackList)


def lookStone(bgr):
    pub_command = rospy.Publisher('judgeError', String, queue_size=1)
    if bgr.shape[0] != cu.Height or bgr.shape[1] != cu.Width:
        #show_info(u'图像尺寸与标定不符')
        pub_command.publish("ImageSizeError")
        raise Exception(u'图像尺寸与标定不符')
    rl, bl = cu.filterStone(bgr)
    rn = [cu.recStone(cu.RedList, cu.RedName, stone) for stone in rl]
    bn = [cu.recStone(cu.BlackList, cu.BlackName, stone) for stone in bl]
    return rl, rn, bl, bn

''' 根据lookStone的结果识别棋盘，返回：(二维数组的盘面, 红色是否在上方) '''
def stone2Board(rl, rn, bl, bn):
    board = [['1' for x in xrange(cu.Cols)] for y in xrange(cu.Rows)]
    red_up = False
    for n in xrange(len(rl)):
        x, y = xy2Grid(rl[n][0])
        board[y][x] = rn[n]
        if (not red_up) and (rn[n]=='k' or rn[n]=='a' or rn[n]=='b') and y < cu.Rows / 2:
            red_up = True
    if not red_up:
        for y in xrange(cu.Rows):
            for x in xrange(cu.Cols):
                if board[y][x] != '1':
                    board[y][x] = chr(ord(board[y][x]) - ord('a') + ord('A'))   # 改为大写字母
    for n in xrange(len(bl)):
        x, y = xy2Grid(bl[n][0])
        board[y][x] = chr(ord(bn[n]) - ord('a') + ord('A')) if red_up else bn[n]
    return board, red_up

def xy2Grid((x, y)):
    grid_x = int(round((x - cu.MinX) / cu.SepX))
    grid_y = int(round((y - cu.MinY) / cu.SepY))
    return grid_x, grid_y


def grid2XY((grid_x, grid_y)):
    x = cu.MinX + int(round(cu.SepX * grid_x))
    y = cu.MinY + int(round(cu.SepY * grid_y))
    return x, y

def hasStone(rl, rn, bl, bn, (grid_x, grid_y)):
    for n in xrange(len(rl)):
        grid = xy2Grid(rl[n][0])
        if grid == (grid_x, grid_y):
            return rl[n], rn[n], True
    for n in xrange(len(bl)):
        grid = xy2Grid(bl[n][0])
        if grid == (grid_x, grid_y):
            return bl[n], bn[n], False

def mergeStone(rl, bl, rn=None, bn=None):
    img = np.zeros((cu.Height, cu.Width), np.uint8)
    for n in xrange(len(rl)):
        mn = n if rn is None else cu.RedName.index(rn[n])
        x, y = rl[n][0]
        r = rl[n][1].shape[0] if rn is None else cu.RedList[mn][1].shape[0]
        r = (r - 1) / 2
        img[y-r:y+r+1, x-r:x+r+1] = rl[n][1] if rn is None else cu.RedList[mn][1]
        cv2.circle(img, (x, y), r, 255, 1)
    for n in xrange(len(bl)):
        mn = n if bn is None else cu.BlackName.index(bn[n])
        x, y = bl[n][0]
        r = bl[n][1].shape[0] if bn is None else cu.BlackList[mn][1].shape[0]
        r = (r - 1) / 2
        img[y-r:y+r+1, x-r:x+r+1] = bl[n][1] if bn is None else cu.BlackList[mn][1]
        cv2.rectangle(img, (x-r, y-r), (x+r+1, y+r+1), 255, 1)
    img_path = rospy.get_param('~path')
    cv2.imwrite('/var/www/html/assets/img/c.png', img)
    return img



def get_chess_name(key,red = True):
    chess = {
        'p': '兵',
        'c': '炮',
        'r': '居',
        'n': '马',
        'b': '象',
        'a': '士',
        'k': '帅'
    }
    name = chess[key]
    if not red:
        name = name.replace('兵','卒')
        name = name.replace('帅','将')
    return name

def show_info(message):
    showwarning(title=None, message=message)

