from orthogonalization import *
from mat import Mat
from vec import Vec
from vecutil import *
from matutil import *
from math import *

## Problem 6
def orthonormalize(L):
    return [Vec(v.D, {k : v[k] / sqrt(v * v) for k in v.D}) for v in orthogonalize(L)]

## Problem 7
def aug_orthonormalize(L):
    A, B = aug_orthogonalize(L)
    c = Vec(set(range(len(A))), {i: sqrt(A[i] * A[i]) for i in range(len(A))})
    A = [Vec(A[i].D, {k: A[i][k] / c[i] for k in A[i].D}) for i in range(len(A))]
    B = [Vec(B[i].D, {k: B[i][k] * c[k] for k in B[i].D}) for i in range(len(B))]
    return A, B
