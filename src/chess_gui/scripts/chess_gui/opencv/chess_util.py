#!/usr/bin/env python
# -*- coding: utf-8 -*-

import cv2
import numpy as np
from std_msgs.msg import String
Rows = 10          
Cols = 9           

CmpRot = 10        

Width = None       
Height = None       
MinRadius = None    


Board = ['rnbakabnr', '111111111', '1c11111c1', 'p1p1p1p1p', '111111111', '111111111', 'p1p1p1p1p', '1c11111c1', '111111111', 'rnbakabnr']

RedList = None     
RedName = None     
BlackList = None    
BlackName = None    

MaxRadius = None   
MinX = None         
MaxX = None
MinY = None
MaxY = None
SepX = None         
SepY = None         


def filterStone(bgr):
   
    gray = cv2.cvtColor(bgr, cv2.COLOR_BGR2GRAY)   
    
    gray = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 11, 2)

    
    gray, contours, hierarchy = cv2.findContours(gray, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
    mask = np.zeros((bgr.shape[0], bgr.shape[1]), np.uint8)
    min_area = 3.14 * MinRadius * MinRadius
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area < min_area or area > min_area * 2:
            continue       
        (x, y), out_r = cv2.minEnclosingCircle(cnt)    
        if 3.14 * out_r * out_r > area * 1.2:
            continue       
        cv2.drawContours(mask, [cnt], 0, 255, -1)

  
    bgr = cv2.bilateralFilter(bgr, 11, 75, 75)     
    gray = cv2.cvtColor(bgr, cv2.COLOR_BGR2GRAY)    
   
    gray = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 11, 2)

   
    gray = cv2.bitwise_and(gray, mask)
    gray = 255 - cv2.bitwise_or(gray, 255 - mask)

    gray = filterSmall(gray, mask)  

   
    stones = []
    mask, contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    for cnt in contours:
        (x, y), out_r = cv2.minEnclosingCircle(cnt)     
        x, y, out_r = int(round(x)), int(round(y)), int(round(out_r+0.5))
        stones.append([(x, y), out_r])

  
    gray = 255 - cv2.bitwise_or(gray, 255 - mask)
    for stone in stones:
        _closeStone(gray, stone)

    gray = filterSmall(gray, mask) 

    for stone in stones:
        (x, y), r = stone
        stone[1] = gray[y-r:y+r+1, x-r:x+r+1]  

    
    gray = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
    bgr = cv2.bitwise_and(bgr, gray)        
    bgr = cv2.cvtColor(bgr, cv2.COLOR_BGR2HSV)
    lower = np.array([150, 30, 30])
    upper = np.array([180, 255, 255])
    red_img = cv2.inRange(bgr, lower, upper)  
    lower = np.array([0, 30, 30])
    upper = np.array([150, 255, 255])
    black_img = cv2.inRange(bgr, lower, upper)  

    red = []
    black = []
    for stone in stones:
        (x, y), r = stone[0], (stone[1].shape[0] - 1) / 2
        img_red = red_img[y-r:y+r+1, x-r:x+r+1]
        img_black = black_img[y-r:y+r+1, x-r:x+r+1]
        if np.sum(img_red) > np.sum(img_black):
            red.append(stone)
        else:
            black.append(stone)
    return red, black


def filterSmall(gray, mask, min_area=None):
    gray, contours, hierarchy = cv2.findContours(gray, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    mask[:, :] = 0
    if min_area is None:
        min_area = MinRadius * MinRadius / 100
    for n in xrange(len(contours)):
        area = cv2.contourArea(contours[n])
        if area > min_area:
            mask = cv2.drawContours(mask, contours, n, 255, -1)
    return cv2.bitwise_and(gray, mask)


def _closeStone(gray, stone):
    (x, y), r = stone
    img_one = gray[y-r:y+r+1, x-r:x+r+1]
    max_cnt = _maxExternal(img_one)
    (xx, yy), out_r = cv2.minEnclosingCircle(max_cnt)     
    if out_r > MinRadius:
      
        mask = np.zeros(img_one.shape, np.uint8)
        cv2.drawContours(mask, [max_cnt], 0, 255, -1)
        mask = 255 - cv2.bitwise_or(img_one, 255 - mask)
        max_cnt = _maxExternal(mask)
        mask[:, :] = 0
        mask = cv2.drawContours(mask, [max_cnt], 0, 255, -1)
        img_one = cv2.bitwise_and(img_one, mask)
        gray[y-r:y+r+1, x-r:x+r+1] = img_one       

        (xx, yy), out_r = cv2.minEnclosingCircle(max_cnt)     
        stone[0] = x - r + int(round(xx)), y - r + int(round(yy))
        stone[1] = int(round(out_r + 0.5))


def _maxExternal(img_one):
   
    img_one, contours, tmp = cv2.findContours(img_one, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    max_area = 0   
    max_cnt = None  
    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area > max_area:
            max_area = area
            max_cnt = cnt
    return max_cnt


def recStone(stones, names, stone):
    r = max(MaxRadius, (stone[1].shape[0] - 1) / 2)
    src = np.zeros((r*2+1, r*2+1), np.uint8)
    dst = np.zeros((r*2+1, r*2+1), np.uint8)
    res = []
    for one in stones:
        _putOne(src, one[1])
        _putOne(dst, stone[1])
        this = [int(np.sum(cv2.bitwise_xor(src, dst)) / 255)]
        for angle in xrange(CmpRot, 360, CmpRot):
            M = cv2.getRotationMatrix2D((r, r), angle, 1)    
            temp = cv2.warpAffine(dst, M, (r*2+1, r*2+1), flags=cv2.INTER_NEAREST)     
            this.append(int(np.sum(cv2.bitwise_xor(src, temp)) / 255))
        res.append(min(this))
    n = min(res)
    return names[res.index(n)]


def _putOne(large, small):
    size = small.shape[0]
    move = (large.shape[0] - size) / 2
    large[move:move+size, move:move+size] = small


def findCorner(img, size):
    res = []
    for r in xrange(1, size-1):
        for c in xrange(1, size-1):
            if img[r, c] > 0:
                dot = 0
                dot += img[r - 1, c - 1] / 255
                dot += img[r - 1, c] / 255
                dot += img[r - 1, c + 1] / 255
                dot += img[r, c - 1] / 255
                dot += img[r, c + 1] / 255
                dot += img[r + 1, c - 1] / 255
                dot += img[r + 1, c] / 255
                dot += img[r + 1, c + 1] / 255
                if 0 < dot <= 4:
                    res.append([c, r, dot])
    return res


def filterBoard(bgr):
    bgr = cv2.bilateralFilter(bgr, 11, 75, 75) 
    gray = cv2.cvtColor(bgr, cv2.COLOR_BGR2GRAY)  
    
    gray = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 11, 2)

    min_area = gray.shape[0] * gray.shape[1] / 16
    min_sep = 10
    mask = np.zeros((bgr.shape[0], bgr.shape[1]), np.uint8)
    gray = filterSmall(gray, mask, min_area)

    gray = 255 - cv2.bitwise_or(gray, 255 - mask)
  
    mask, contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    x, y, w, h = cv2.boundingRect(contours[0]) 
    gray = cv2.rectangle(gray, (x, y+h/2-min_sep), (x+w, y+h/2+min_sep), 255, -1)     

    gray = filterSmall(gray, mask, min_area)
    gray = 255 - cv2.bitwise_or(gray, 255 - mask)
    gray = filterSmall(gray, mask, min_area)

    corner_lu = []
    corner_rd = []
    mask, contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    for cnt in contours:
        x, y, w, h = cv2.boundingRect(cnt)
        corner_lu.append([(x, y),(x+w, y+h), (x+y, x+w+y+h)])
        corner_rd.append([(x, y),(x+w, y+h), (x+y, x+w+y+h)])
    corner_lu.sort(lambda a, b: -1 if a[2][0] < b[2][0] else 1)
    corner_rd.sort(lambda a, b: -1 if a[2][1] > b[2][1] else 1)

  
    img = np.zeros((min_sep*2+2, min_sep*2+2), np.uint8)
    x, y = corner_lu[0][0]
    img[1:min_sep*2+1, 1:min_sep*2+1] = mask[y:y+min_sep*2, x:x+min_sep*2]
    corner_lu = findCorner(img, min_sep*2+2)
    corner_lu.sort(lambda a, b: -1 if sum(a) < sum(b) else 1)
    x_lu = x + corner_lu[0][0] - 1
    y_lu = y + corner_lu[0][1] - 1

    
    img[:, :] = 0
    x, y = corner_rd[0][1]
    img[1:min_sep*2+1, 1:min_sep*2+1] = mask[y-min_sep*2:y, x-min_sep*2:x]
    corner_rd = findCorner(img, min_sep*2+2)
    corner_rd.sort(lambda a, b: -1 if sum(a) > sum(b) else 1)
    x_rd = x - min_sep*2 + corner_rd[0][0] - 1
    y_rd = y - min_sep*2 + corner_rd[0][1] - 1
    return (x_lu, y_lu), (x_rd, y_rd)
