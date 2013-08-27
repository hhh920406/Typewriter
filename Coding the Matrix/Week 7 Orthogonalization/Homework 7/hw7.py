from orthogonalization import *
import orthonormalization
from mat import Mat
from vec import Vec
from vecutil import *
from matutil import *
from QR import *
from triangular import *

## Problem 1
def basis(vlist):
    return [v for v in orthogonalize(vlist) if v * v > 1e-20]

## Problem 2
def subset_basis(vlist):
    return [vlist[i] for i in range(len(vlist)) if orthogonalize(vlist)[i] * orthogonalize(vlist)[i] > 1e-20]

## Problem 3
def orthogonal_vec2rep(Q, b):
    return Q * b

## Problem 4
def orthogonal_change_of_basis(A, B, a):
    return (a * A) * B

## Problem 5
def orthonormal_projection_orthogonal(W, b):
    return project_orthogonal(b, list(mat2rowdict(W).values()))

## Problem 8
least_squares_A1 = listlist2mat([[8, 1], [6, 2], [0, 6]])
least_squares_Q1 = listlist2mat([[.8,-0.099],[.6, 0.132],[0,0.986]])
least_squares_R1 = listlist2mat([[10,2],[0,6.08]]) 
least_squares_b1 = list2vec([10, 8, 6])

x_hat_1 = list2vec([1.08, 0.984])

least_squares_A2 = listlist2mat([[3, 1], [4, 1], [5, 1]])
least_squares_Q2 = listlist2mat([[.424, .808],[.566, .115],[.707, -.577]])
least_squares_R2 = listlist2mat([[7.07, 1.7],[0,.346]])
least_squares_b2 = list2vec([10,13,15])

x_hat_2 = list2vec([2.5, 2.66])

## Problem 9
def QR_solve(A, b):
    Q, R = factor(A)
    return triangular_solve(mat2rowdict(R), list(A.D[1]), Q.transpose() * b)

