from mat import Mat
from vec import Vec
from matutil import *
from vecutil import *
from GF2 import one
from math import *

## Problem 1
echelon_form_1 = [[1, 2, 0, 2, 0],
                  [0, 1, 0, 3, 4],
                  [0, 0, 2, 3, 4],
                  [0, 0, 0, 2, 0],
                  [0, 0, 0, 0, 4]]

echelon_form_2 = [[0, 4, 3, 4, 4],
                  [0, 0, 4, 2, 0],
                  [0, 0, 0, 0, 1],
                  [0, 0, 0, 0, 0]]

echelon_form_3 = [[1, 0, 0, 1],
                  [0, 0, 0, 1],
                  [0, 0, 0, 0]]

echelon_form_4 = [[1, 0, 0, 0],
                  [0, 1, 0, 0],
                  [0, 0, 0, 0],
                  [0, 0, 0, 0]]

## Problem 2
def is_echelon(A):
    firstNonZero = [i + len(A) for i in range(len(A))]
    for i in range(len(A)):
        for j in range(len(A[i])):
            if fabs(A[i][j]) > 1e-8:
                firstNonZero[i] = j
                break
    for i in range(1, len(A)):
        if firstNonZero[i] <= firstNonZero[i - 1]:
            return False
    return True

## Problem 3
echelon_form_vec_a = [1, 0, 3, 0]
echelon_form_vec_b = [-3, 0, -2, 3]
echelon_form_vec_c = [-5, 0, 2, 0, 2]

## Problem 4
solving_with_echelon_form_a = None
solving_with_echelon_form_b = [21, 0, 2, 0, 0]

## Problem 5
def echelon_solve(rowlist, label_list, b):
    newlist = []
    newb = []
    visit = [False for i in range(len(rowlist))]
    for c in label_list:
        for r in range(len(rowlist)):
            if not visit[r]:
                if rowlist[r][c] == one:
                    for rr in range(r + 1, len(rowlist)):
                        if not visit[rr]:
                            if rowlist[rr][c] == one:
                                for i in range(c, len(label_list)):
                                    cc = label_list[i]
                                    rowlist[rr][cc] = rowlist[rr][cc] + rowlist[rr][cc]
                                b[rr] = b[rr] + b[r]
                    newlist.append(rowlist[r])
                    newb.append(b[r])
                    visit[r] = True
                    break
    for r in range(len(rowlist)):
        if not visit[r]:
            newlist.append(rowlist[r])
            newb.append(b[r])
    x = Vec({u for u in label_list}, {})
    for r in range(len(rowlist) - 1, -1, -1):
        temp = newb[r]
        for i in range(len(label_list)):
            c = label_list[i]
            if newlist[r][c] == one:
                temp = newb[r]
                for j in range(i + 1, len(label_list)):
                    cc = label_list[j]
                    temp = temp + x[cc] * newlist[r][cc]
                x[c] = temp
                break
    return x

## Problem 6
rowlist = [ ... ]    # Provide as a list of Vec instances
label_list = [ ... ] # Provide as a list
b = [ ... ]          # Provide as a list

## Problem 7
null_space_rows_a = {...} # Put the row numbers of M from the PDF



## Problem 8
null_space_rows_b = {...}



## Problem 9
# Write each vector as a list
closest_vector_1 = [...]
closest_vector_2 = [...]
closest_vector_3 = [...]



## Problem 10
# Write each vector as a list

project_onto_1 = [...]
projection_orthogonal_1 = [...]

project_onto_2 = [...]
projection_orthogonal_2 = [...]

project_onto_3 = [...]
projection_orthogonal_3 = [...]



## Problem 11
norm1 = ...
norm2 = ...
norm3 = ...

