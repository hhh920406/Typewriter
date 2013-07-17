#!/usr/bin/python
# -*- coding: utf-8 -*-

def solveIt(n):
    ans = [[0 for j in range(n)] for i in range(n)]
    x = 0
    y = n >> 1
    for i in range(n * n):
        ans[x][y] = i + 1
        tx = (x - 1 + n) % n
        ty = (y + 1) % n
        if ans[tx][ty] == 0:
            x = tx;
            y = ty;
        else:
            x = (x + 1) % n
    outputData = str(n) + "\n"
    for i in range(n):
        for j in range(n):
            outputData += str(ans[n - j - 1][i]) + " "
        outputData += "\n"
    return outputData

import sys

if __name__ == "__main__":
    if len(sys.argv) > 1:
        try:
            n = int(sys.argv[1].strip())
        except:
            print sys.argv[1].strip(), 'is not an integer'
        print 'Solving Size:', n
        print(solveIt(n))
    
    else:
        print('This test requires an instance size.  Please select the size of problem to solve. (i.e. python magicSquareSolver.py 3)')

