from vecutil import list2vec
from solver import solve
from matutil import *
from mat import Mat
from GF2 import one
from vec import *
from independence import *
from hw4 import *
from triangular import *

## Problem 1
w0 = list2vec([1,0,0])
w1 = list2vec([0,1,0])
w2 = list2vec([0,0,1])

v0 = list2vec([1,2,3])
v1 = list2vec([1,3,3])
v2 = list2vec([0,3,3])

exchange_S0 = [w0, w1, w2]
exchange_S1 = [v0, w1, w2]
exchange_S2 = [v0, v1, w2]
exchange_S3 = [v0, v1, v2]

## Problem 2
w0 = list2vec([0,one,0])
w1 = list2vec([0,0,one])
w2 = list2vec([one,one,one])

v0 = list2vec([one,0,one])
v1 = list2vec([one,0,0])
v2 = list2vec([one,one,0])

exchange_2_S0 = [w0, w1, w2]
exchange_2_S1 = [w0, w1, v1]
exchange_2_S2 = [w0, v0, v1]
exchange_2_S3 = [v0, v1, v2]

## Problem 3
def morph(S, B):
    TS = []
    for i in range(len(S)):
        TS.append(S[i])
    res = []
    for i in range(len(B)):
        for j in range(len(TS)):
            T = []
            for k in range(len(TS)):
                if j != k:
                    T.append(TS[k])
            for k in range(i + 1):
                T.append(B[k])
            if rank(T) == len(B):
                w = TS[j]
                TS.remove(TS[j])
                break
        res.append((B[i], w))
    return res

## Problem 4
row_space_1 = [list2vec(v) for v in [[1, 2, 0], [0, 2, 1]]]
col_space_1 = [list2vec(v) for v in [[1, 0], [0, 1]]]

row_space_2 = [list2vec(v) for v in [[1, 4, 0, 0], [0, 2, 2, 0], [0, 0, 1, 1]]]
col_space_2 = [list2vec(v) for v in [[1, 0, 0], [4, 2, 0], [0, 2, 1]]]

row_space_3 = [list2vec(v) for v in [[1]]]
col_space_3 = [list2vec(v) for v in [[1, 2, 3]]]

row_space_4 = [list2vec(v) for v in [[1, 0], [2, 1]]]
col_space_4 = [list2vec(v) for v in [[1, 2, 3], [0, 1, 4]]]

## Problem 5
def my_is_independent(L): 
    return rank(L) == len(L)

## Problem 6
def subset_basis(T): 
    S = [T[0]]
    T.remove(T[0])
    for i in range(len(T)):
        for j in range(len(T)):
            S.append(T[j])
            if not is_superfluous(S, len(S) - 1):
                T.remove(T[j])
                break
            S.remove(T[j])
    return S

## Problem 7
def my_rank(L): 
    return len(subset_basis(L))

## Problem 8
only_share_the_zero_vector_1 = True
only_share_the_zero_vector_2 = True
only_share_the_zero_vector_3 = True

## Problem 9
def direct_sum_decompose(U_basis, V_basis, w):
    T = []
    for u in U_basis:
        T.append(u)
    for v in V_basis:
        T.append(v)
    rep = vec2rep(T, w)
    u = Vec(w.D, {})
    v = Vec(v.D, {})
    for i in range(len(U_basis)):
        u = u + scalar_mul(U_basis[i], rep[i])
    for i in range(len(V_basis)):
        v = v + scalar_mul(V_basis[i], rep[i + len(U_basis)])
    return (u, v)

## Problem 10
def is_invertible(M): 
    if len(M.D[0]) != len(M.D[1]):
        return False
    L = [v for v in mat2rowdict(M).values()]
    return rank(L) == len(L)

## Problem 11
def find_matrix_inverse(A):
    B = Mat((A.D[1], A.D[0]), {})
    E = mat2coldict(identity(A.D[0], one))
    for i in A.D[0]:
        x = solve(A, E[i])
        for j in A.D[1]:
            B[(j, i)] = x[j]
    return B

## Problem 12
def find_triangular_matrix_inverse(A):
    LA = [v for v in mat2rowdict(A).values()]
    B = Mat((A.D[1], A.D[0]), {})
    E = mat2coldict(identity(A.D[0], 1))
    for i in A.D[0]:
        x = triangular_solve_n(LA, E[i])
        for j in x.D:
            B[(j, i)] = x[j]
    return B
