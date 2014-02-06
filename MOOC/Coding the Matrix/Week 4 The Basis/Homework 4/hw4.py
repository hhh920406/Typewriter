from GF2 import one
from math import sqrt, pi
from matutil import *
from solver import solve
from vec import Vec, scalar_mul
from vecutil import list2vec

## Problem 1
rep_1 = [1, 1, 0]
rep_2 = [0.5, 1, 1]
rep_3 = [0, 1, -1]

## Problem 2
lin_comb_coefficients_1 = [3, -1, 1]
lin_comb_coefficients_2 = [0.5, -1.5, 1]
lin_comb_coefficients_3 = [0.5, -5.5, 4]
lin_comb_coefficients_4 = [1, -2, 1]

## Problem 3
gf2_rep_1 = [one, 0, one, 0]
gf2_rep_2 = [one, 0, 0, one]
gf2_rep_3 = [one, one, 0, one]

## Problem 4
gf2_lc_rep_1 = [0, 0, 0, 0, 1, 1, 0, 0]
gf2_lc_rep_2 = [0, 0, 0, 0, 0, 0, 1, 1]
gf2_lc_rep_3 = [1, 0, 0, 1, 0, 0, 0, 0]
gf2_lc_rep_4 = [1, 0, 1, 0, 0, 0, 0, 0]

## Problem 5
lin_dep_R_1 = [-2, 1, 1]
lin_dep_R_2 = [-28, 7, -4]
lin_dep_R_3 = [-3, 0, 0, 10, 30]

## Problem 6
linear_dep_R_1 = [-1, 1, -3]
linear_dep_R_2 = [2 * pi, 1, pi * sqrt(2) / 2]
linear_dep_R_3 = [1, 1, 1, 1, 1]

## Problem 7
u = 1
v = 1
w = 1
sum_to = 'v'

## Problem 8
indep_vec_1 = Vec({0, 1, 2}, {0:1, 1:0, 2:0})
indep_vec_2 = Vec({0, 1, 2}, {0:0, 1:1, 2:0})
indep_vec_3 = Vec({0, 1, 2}, {0:0, 1:0, 2:1})
indep_vec_4 = Vec({0, 1, 2}, {0:1, 1:1, 2:1})

## Problem 9
zero_comb_1 = [1, 1, 0, 1]
zero_comb_2 = [0, 1, 1, 1]
zero_comb_3 = [1, 1, 0, 0, 1]

## Problem 10
sum_to_zero_1 = [0, one, 0, one, one]
sum_to_zero_2 = [0, one, 0, one, one, 0, 0]
sum_to_zero_3 = [one, 0, one, one, one]
sum_to_zero_4 = [one, one, one, one, one, 0, 0]

## Problem 11
exchange_1 = [0, 0, 1, 0, 0]
exchange_2 = [0, 0, 0, 1, 0]
exchange_3 = [0, 0, 0, 0, 1]

## Problem 12
replace_1 = 'v3'
replace_2 = 'v1'
replace_3 = 'v1'

## Problem 13
def rep2vec(u, veclist):
    return sum([scalar_mul(veclist[i], u[i]) for i in range(len(veclist))])

## Problem 14
def vec2rep(veclist, v):
    return solve(coldict2mat({i: veclist[i] for i in range(len(veclist))}), v)

## Problem 15
def is_superfluous(L, i):
    A = coldict2mat({j: L[j] for j in range(len(L)) if i != j})
    b = L[i]
    u = solve(A, b)
    residual = b - A * u
    return residual * residual < 1e-14

## Problem 16
def is_independent(L):
    return all(not is_superfluous(L, i) for i in range(len(L)))

## Problem 17
def superset_basis(S, L):
    T = []
    for i in range(len(S)):
        T.append(S[i])
        if len(T) > 1:
            if is_superfluous(T, len(T) - 1):
                T.pop()
    for i in range(len(L)):
        T.append(L[i])
        if len(T) > 1:
            if is_superfluous(T, len(T) - 1):
                T.pop()
    return T

## Problem 18
def exchange(S, A, z):
    u = solve(coldict2mat({i: S[i] for i in range(len(S))}), z)
    for i in range(len(S)):
        if S[i] not in A and u[i] > 1e-7:
            return S[i]
