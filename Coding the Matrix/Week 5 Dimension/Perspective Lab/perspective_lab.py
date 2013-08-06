from mat import Mat
from vec import Vec
from solver import solve
from matutil import *

## Task 1
def move2board(v):
    y1 = v['y1']
    y2 = v['y2']
    y3 = v['y3']
    return Vec({'y1','y2','y3'}, {'y1': y1 / y3, 'y2': y2 / y3, 'y3': y3 / y3})

## Task 2
def make_equations(x1, x2, w1, w2): 
    '''
    Input:
        - x1 & x2: photo coordinates of a point on the board
        - y1 & y2: whiteboard coordinates of a point on the board
    Output:
        - List [u,v] where u*h = 0 and v*h = 0
    '''
    domain = {(a, b) for a in {'y1', 'y2', 'y3'} for b in {'x1', 'x2', 'x3'}}
    u = Vec(domain, ...)
    v = Vec(domain, ...)
    return [u, v]


## Task 3
H = ...

## Task 4
def mat_move2board(Y):
    return coldict2mat({k: move2board(v) for (k, v) in mat2coldict(Y).items()})
