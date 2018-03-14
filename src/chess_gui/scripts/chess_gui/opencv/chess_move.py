#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import cv2
import chess_look as cl
from std_msgs.msg import String

_red_stones = {
    'k' : ((4,0), ),
    'a' : ((3,0), (5,0)),
    'b' : ((2,0), (6,0)),
    'n' : ((1,0), (7,0)),
    'r' : ((0,0), (8,0)),
    'c' : ((1,2), (7,2)),
    'p' : ((0,3), (2,3), (4,3), (6,3), (8,3))
}
_black_stones = {
    'k' : ((4,9), ),
    'a' : ((3,9), (5,9)),
    'b' : ((2,9), (6,9)),
    'n' : ((1,9), (7,9)),
    'r' : ((0,9), (8,9)),
    'c' : ((1,7), (7,7)),
    'p' : ((0,6), (2,6), (4,6), (6,6), (8,6))
}

_blank = [(x,y) for x in xrange(9) for y in (4,5,1,8)]     
_blank.extend([(x,y) for x in (0,2,3,4,5,6,8) for y in (2,7)])
_blank.extend([(x,y) for x in (1,3,5,7) for y in (3,6)])


def moveStone(rl, rn, bl, bn):
    stones = []
    stones.extend(rl)
    stones.extend(bl)
    grid = [cl.xy2Grid(stone[0]) for stone in stones]  
    sep = int(min(cl.cu.SepX, cl.cu.SepY) * 0.9)       

    for n in xrange(len(stones)):
        is_red = n < len(rl)
        name = rn[n] if is_red else bn[n-len(rl)]
        target = _red_stones[name] if is_red else _black_stones[name]  
        if grid[n] in target and _countGrid(grid, grid[n]) == 1:
            gxy = _atGrid(grid[n], stones[n][0], sep)
            if gxy is None:
                continue        
            elif _noStone(stones, gxy, sep, n):
                xy = stones[n][0]
                stones[n][0] = gxy
                return n if is_red else n-len(rl), is_red, xy, gxy  
            continue    
        if _noStone(stones, stones[n][0], sep, n):
            gxy = _checkTarget(stones, grid, target, sep, n)          
            if gxy is None and grid[n] not in _blank:
                gxy = _checkTarget(stones, grid, _blank, sep, n)       
            if gxy is not None:
                xy = stones[n][0]
                stones[n][0] = gxy
                return n if is_red else n - len(rl), is_red, xy, gxy   
    return None


def _countGrid(grid, (grid_x, grid_y)):
    count = 0
    for (gx, gy) in grid:
        if (gx, gy) == (grid_x, grid_y):
            count += 1
    return count


def _atGrid((grid_x, grid_y), (x, y), sep):
    gx, gy = cl.grid2XY((grid_x, grid_y))
    x = gx - x
    y = gy - y
    if x * x + y * y > sep * sep / (5 * 5):
        return gx, gy
    return None


def _noStone(stones, (x, y), sep, nocheck):
    for n in xrange(len(stones)):
        if n == nocheck:
            continue
        ox, oy = stones[n][0]
        if (x - ox) * (x - ox) + (y - oy) * (y - oy) < sep * sep:
            return False
    return True

def _checkTarget(stones, grid, target, sep, nocheck=-1):
    for grid_xy in target:
        x, y = cl.grid2XY(grid_xy)
        if grid_xy not in grid and _noStone(stones, (x, y), sep, nocheck):
            return x, y
    return None



def show(img, name='img', wait=0):
    img = cv2.resize(img, None, fx=1, fy=0.6)
    cv2.imshow(name, img)
    if cv2.waitKey(wait) == 27:
        cv2.destroyAllWindows()
        exit()

