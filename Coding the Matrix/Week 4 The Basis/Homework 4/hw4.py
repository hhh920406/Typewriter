from GF2 import one
from math import sqrt, pi
from matutil import coldict2mat
from solver import solve
from vec import Vec, scalar_mul

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
gf2_rep_1 = [1, 0, 1, 0]
gf2_rep_2 = [1, 0, 0, 1]
gf2_rep_3 = [1, 1, 0, 1]

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
sum_to_zero_1 = [0, 1, 0, 1, 1]
sum_to_zero_2 = [0, 1, 0, 1, 1, 0, 0]
sum_to_zero_3 = [1, 0, 1, 1, 1]
sum_to_zero_4 = [1, 1, 1, 1, 1, 0, 0]

## Problem 11
exchange_1 = [0, 0, 1, 0, 0]
exchange_2 = [0, 0, 0, 1, 0]
exchange_3 = [0, 0, 0, 0, 1]

## Problem 12
replace_1 = [1, 0, 0, 1, 0, 0, 0, 0]
replace_2 = [1, 1, 0, 0, 0, 0, 0, 0]
replace_3 = [0, 1, 0, 0, 1, 0, 0, 0]

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
    '''
    Input: 
        - S: linearly independent list of Vec instances
        - L: list of Vec instances such that every vector in S is in Span(L)
    Output:
        Linearly independent list T containing all vectors (as instances of Vec)
        such that the span of T is the span of L (i.e. T is a basis for the span
        of L).
    Example:
        >>> a0 = Vec({'a','b','c','d'}, {'a':1})
        >>> a1 = Vec({'a','b','c','d'}, {'b':1})
        >>> a2 = Vec({'a','b','c','d'}, {'c':1})
        >>> a3 = Vec({'a','b','c','d'}, {'a':1,'c':3})
        >>> superset_basis([a0, a3], [a0, a1, a2]) == [Vec({'a', 'c', 'b', 'd'},{'a': 1}), Vec({'a', 'c', 'b', 'd'},{'b':1}),Vec({'a', 'c', 'b', 'd'},{'c': 1})]
        True
    '''
    pass



## Problem 18
def exchange(S, A, z):
    '''
    Input:
        - S: a list of vectors, as instances of your Vec class
        - A: a list of vectors, each of which are in S, with len(A) < len(S)
        - z: an instance of Vec such that A+[z] is linearly independent
    Output: a vector w in S but not in A such that Span S = Span ({z} U S - {w})
    Example:
        >>> S = [list2vec(v) for v in [[0,0,5,3],[2,0,1,3],[0,0,1,0],[1,2,3,4]]]
        >>> A = [list2vec(v) for v in [[0,0,5,3],[2,0,1,3]]]
        >>> z = list2vec([0,2,1,1])
        >>> exchange(S, A, z) == Vec({0, 1, 2, 3},{0: 0, 1: 0, 2: 1, 3: 0})
        True
    '''
    pass

