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
    domain = {(a, b) for a in {'y1', 'y2', 'y3'} for b in {'x1', 'x2', 'x3'}}
    u = Vec(domain, {})
    v = Vec(domain, {})
    u[('y3', 'x1')] = w1 * x1;
    u[('y3', 'x2')] = w1 * x2;
    u[('y3', 'x3')] = w1;
    u[('y1', 'x1')] = -x1;
    u[('y1', 'x2')] = -x2;
    u[('y1', 'x3')] = -1;
    v[('y3', 'x1')] = w2 * x1;
    v[('y3', 'x2')] = w2 * x2;
    v[('y3', 'x3')] = w2;
    v[('y2', 'x1')] = -x1;
    v[('y2', 'x2')] = -x2;
    v[('y2', 'x3')] = -1;
    return [u, v]

## Task 3
(u1, v1) = make_equations(358, 36, 0, 0)
(u2, v2) = make_equations(329, 597, 0, 1)
(u3, v3) = make_equations(592, 157, 1, 0)
(u4, v4) = make_equations(580, 483, 1, 1)
domain = {(a, b) for a in {'y1', 'y2', 'y3'} for b in {'x1', 'x2', 'x3'}}
w = Vec(domain, {('y1', 'x1'): 1})
L = rowdict2mat({0: u1, 1: v1, 2: u2, 3: v2, 4: u3, 5: v3, 6: u4, 7: v4, 8: w})
b = Vec({i for i in range(9)}, {8: 1})
h = solve(L, b)
H = Mat(({'y1', 'y2', 'y3'}, {'x1', 'x2', 'x3'}), {k:v for (k, v) in h.f.items()})

## Task 4
def mat_move2board(Y):
    return coldict2mat({k: move2board(v) for (k, v) in mat2coldict(Y).items()})
