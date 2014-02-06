from vec import Vec
from mat import Mat
from bitutil import noise
from GF2 import one
from vecutil import *
from matutil import *
from bitutil import *

## Task 1 part 1
G = listlist2mat([[one, 0, one, one], [one, one, 0, one], [0, 0, 0, one], [one, one, one, 0], [0, 0, one, 0], [0, one, 0, 0], [one, 0, 0, 0]])

## Task 1 part 2
encoding_1001 = [0, 0, one, one, 0, 0, one]

## Task 2
R = listlist2mat([[one, one, 0, one, 0, 0, 0], [one, 0, one, one, 0, 0, 0], [0, one, one, one, 0, 0, 0], [0, 0, one, 0, 0, 0, 0]])

## Task 3
H = listlist2mat([[0, 0, 0, one, one, one, one], [0, one, one, 0, 0, one, one], [one, 0, one, 0, one, 0, one]])

## Task 4 part 1
def find_error(e):
    H = listlist2mat([[0, 0, 0, one, one, one, one], [0, one, one, 0, 0, one, one], [one, 0, one, 0, one, 0, one]])
    return Vec(H.D[1], {key : one for (key, v) in mat2coldict(H).items() if v == e})

## Task 4 part 2
non_codeword = Vec({0,1,2,3,4,5,6}, {0: one, 1:0, 2:one, 3:one, 4:0, 5:one, 6:one})
error_vector = Vec({0,1,2,3,4,5,6}, {6:one})
code_word = Vec({0,1,2,3,4,5,6}, {0: one, 1:0, 2:one, 3:one, 4:0, 5:one, 6:0})
original = R * code_word


## Task 5
def find_error_matrix(S):
    M = Mat(({0,1,2,3,4,5,6}, S.D[1]), {})
    for (j, v) in mat2coldict(S).items():
        v = find_error(v)
        for i in v.D:
            if v[i] == one:
                M[(i, j)] = one
    return M

## Task 6
s = "I'm trying to free your mind, Neo. But I can only show you the door. You’re the one that has to walk through it."
P = bits2mat(str2bits(s))

## Task 7
C = G * P
bits_before = 896
bits_after = 1568

## Task 8
def correct(A):
    H = listlist2mat([[0, 0, 0, one, one, one, one], [0, one, one, 0, 0, one, one], [one, 0, one, 0, one, 0, one]])
    return find_error_matrix(H * A) + A
