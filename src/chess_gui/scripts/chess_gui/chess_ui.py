#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Time    : 17-12-8 上午10:32
# @Author  : yu
# @File    :
# @Desc    :

from Tkinter import *
from PIL import Image
from PIL import ImageTk
import tkFont


import rospy
FEN_UP = 'rnbakcp'  
FEN_DOWN = 'RNBAKCP'  


SPACE = 51

PADDING = 30

LINE_WIDTH = 1


price_coordinates = {
   'R1': (0, 0),
   'R2': (8, 0),
   'N1': (1, 0),
   'N2': (7, 0),
   'B1': (2, 0),
   'B2': (6, 0),
   'A1': (3, 0),
   'A2': (5, 0),
   'K1': (4, 0),
   'C1': (1, 2),
   'C2': (7, 2),
   'P1': (0, 3),
   'P2': (2, 3),
   'P3': (4, 3),
   'P4': (6, 3),
   'P5': (8, 3),

   'r1': (0, 9),
   'r2': (8, 9),
   'n1': (1, 9),
   'n2': (7, 9),
   'b1': (2, 9),
   'b2': (6, 9),
   'a1': (3, 9),
   'a2': (5, 9),
   'k1': (4, 9),
   'c1': (1, 7),
   'c2': (7, 7),
   'p1': (0, 6),
   'p2': (2, 6),
   'p3': (4, 6),
   'p4': (6, 6),
   'p5': (8, 6),
}

img_cache = {
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
}

price_dist = {
   'R': 'rr.png',
   'N': 'rn.png',
   'B': 'rb.png',
   'A': 'ra.png',
   'K': 'rk.png',
   'C': 'rc.png',
   'P': 'rp.png',

   'r': 'br.png',
   'n': 'bn.png',
   'b': 'bb.png',
   'a': 'ba.png',
   'k': 'bk.png',
   'c': 'bc.png',
   'p': 'bp.png',
}

im_keys={}

'初始化棋盘'
def draw_chess(root):
  width = SPACE * 8 + 8
  height = SPACE * 9 + 9
 

  can = Canvas(root,
               width=width+2*PADDING,
               height=height+2*PADDING,
               bg='#f8ecbc'
               )
  
  can.pack(side=LEFT,padx=50)

  can.create_rectangle(1,1, width+2*PADDING, height+2*PADDING, outline='black', width=5)
  for i in range(10):
    can.create_line((PADDING, i * (SPACE+1) + PADDING), (width+PADDING, i * (SPACE+1) + PADDING), width=LINE_WIDTH)

  for i in range(9):
    if i==0 or i==8:
     can.create_line((i * (SPACE+1) + PADDING, PADDING), (i * (SPACE+1) + PADDING, height + PADDING), width=LINE_WIDTH)
    else:
     can.create_line((i * (SPACE+1) + PADDING, PADDING), (i * (SPACE+1) + PADDING, SPACE*4+4 + PADDING), width=LINE_WIDTH)
     can.create_line((i * (SPACE + 1) + PADDING, PADDING+SPACE*5+5), (i * (SPACE + 1) + PADDING, height + PADDING), width=LINE_WIDTH)
 
  ft=tkFont.Font(family = 'Fixdsys',size = 20,weight = tkFont.BOLD)
  can.create_text(PADDING+SPACE, PADDING+SPACE*4+SPACE/2+5, text="楚河", font = ft)
  can.create_text(PADDING+width-SPACE, PADDING+SPACE*4+SPACE/2+5, text="汉界", font = ft)

  can.create_line((PADDING + SPACE * 3 + 3, PADDING), (PADDING + SPACE * 5 + 5, PADDING + SPACE * 2 + 2),
                 width=LINE_WIDTH)
  can.create_line((PADDING + SPACE * 5 + 5, PADDING), (PADDING + SPACE * 3 + 3, PADDING + SPACE * 2 + 2),
                 width=LINE_WIDTH)

  can.create_line((PADDING + SPACE * 3 + 3, PADDING+SPACE * 7 + 7), (PADDING + SPACE * 5 + 5, PADDING + height),
                 width=LINE_WIDTH)
  can.create_line((PADDING + SPACE * 5 + 5, PADDING+SPACE * 7 + 7), (PADDING + SPACE * 3 + 3, PADDING + height),
                 width=LINE_WIDTH)
  return can


def capture_price(can,pick):
    print ('-----')
    global price_coordinates
    coordinates = price_coordinates
    for key, value in coordinates.items():
        if value == pick:
           can.delete(im_keys[key])
           price_coordinates[key] = None
    print ('-----')

def move_price(can,a1,a2):
    print ('-----')
    global price_coordinates
    coordinates = price_coordinates
    for key, value in coordinates.items():
        if value == a1:
          can.delete(im_keys[key])
          price_coordinates[key] = None
          x,y=a2
          a2= ((x+1)*SPACE+x-15, (y+1)*SPACE+y-15)
          im_keys[key] = can.create_image(a2, image=img_cache[key])
        
          price_coordinates[key] = a2
    print ('-----')



def update_price_coordinates(can, coordinates):
    print ('-----')
    path = rospy.get_param('~path')
    global img_cache, price_coordinates, im_keys
    price_coordinates = coordinates
    for key, value in coordinates.items():
        img_cache[key] = Image.open(path+price_dist[key[0]])
        img_cache[key] = ImageTk.PhotoImage(img_cache[key])
        if value is not None:
            x, y = value
            value = ((x+1)*SPACE+x-15, (y+1)*SPACE+y-15)
            im = can.create_image(value, image=img_cache[key])
            im_keys[key] = im
    print ('-----')
