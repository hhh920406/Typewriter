#!/usr/bin/python
# -*- coding: utf-8 -*-

def solveIt(n):
    outputData = str(n) + "\n"
    for i in range(n):
        if i & 1:
            outputData += str(n - ((i + 1) >> 1)) + " "
        else:
            outputData += str(i >> 1) + " "
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
        print('This test requires an instance size.  Please select the size of problem to solve. (i.e. python allIntervalSeriesSolver.py 5)')

