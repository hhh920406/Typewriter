#!/usr/bin/python
# -*- coding: utf-8 -*-

def solveIt(n):
    outputData = str(n) + "\n"
    outputData += str(n - 4) + " "
    outputData += "2 1 "
    for i in range(n - 7):
        outputData += "0 "
    outputData += "1 0 0 0"
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
        print('This test requires an instance size.  Please select the size of problem to solve. (i.e. python magicSeriesSolver.py 5)')

