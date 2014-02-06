from vec import Vec
from vecutil import *
from mat import Mat
from matutil import *
import math

## Task 1
def identity(labels = {'x','y','u'}):
    return Mat((labels, labels), {(i, i) : 1 for i in labels})

## Task 2
def translation(x,y):
    m = identity()
    m[('x', 'u')] = x
    m[('y', 'u')] = y
    return m

## Task 3
def scale(a, b):
    m = identity()
    m[('x', 'x')] = a
    m[('y', 'y')] = b
    return m

## Task 4
def rotation(angle):
    m = identity()
    m[('x', 'x')] = math.cos(angle)
    m[('x', 'y')] = -math.sin(angle)
    m[('y', 'x')] = math.sin(angle)
    m[('y', 'y')] = math.cos(angle)
    return m

## Task 5
def rotate_about(x,y,angle):
    return translation(x, y) * rotation(angle) * translation(-x, -y)

## Task 6
def reflect_y():
    m = identity()
    m[('x', 'x')] = -1
    return m

## Task 7
def reflect_x():
    m = identity()
    m[('y', 'y')] = -1
    return m
    
## Task 8    
def scale_color(scale_r,scale_g,scale_b):
    m = identity({'r', 'g', 'b'})
    m[('r', 'r')] = scale_r
    m[('g', 'g')] = scale_g
    m[('b', 'b')] = scale_b
    return m

## Task 9
def grayscale():
    m = identity({'r', 'g', 'b'})
    m[('r', 'r')] = m[('g', 'r')] = m[('b', 'r')] = 77.0 / 256.0
    m[('r', 'g')] = m[('g', 'g')] = m[('b', 'g')] = 151.0 / 256.0
    m[('r', 'b')] = m[('g', 'b')] = m[('b', 'b')] = 28.0 / 256.0
    return m

## Task 10
def reflect_about(p1,p2):
    theta = math(p2.y - p1.y, p2.x - p1.x)
    m = rotate_about(p1.x, p1.y, -theta) * translation(0, -p1.y) * reflect_x() * translation(0, p1.y) * rotate_about(p1.x, p1.y, theta)


