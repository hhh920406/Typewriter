from vec import *
from vecutil import *
from GF2 import *

## Problem 1
def vec_select(veclist, k): 
    return [v for v in veclist if getitem(v, k) == 0]

def vec_sum(veclist, D): 
    vec_sum = zero_vec(D)
    for vec in veclist:
        for d in vec.f.keys():
            setitem(vec_sum, d, getitem(vec_sum, d) + getitem(vec, d))
    return vec_sum

def vec_select_sum(veclist, k, D): 
    return vec_sum(vec_select(veclist, k), D)

## Problem 2
def scale_vecs(vecdict):
    return [scalar_mul(vec, 1 / k) for (k, vec) in vecdict.items()]

## Problem 3
def GF2_Span(D, L, span, take, depth):
    if depth == len(L):
        veclist = []
        for i in range(depth):
            if take[i] == 1:
                veclist.append(L[i])
        span.append(vec_sum(veclist, D))
        return
    take[depth] = 0
    GF2_Span(D, L, span, take, depth + 1)
    take[depth] = 1
    GF2_Span(D, L, span, take, depth + 1)

def GF2_span(D, L):
    span = []
    take = [0 for i in range(len(L))]
    if len(L) > 0:
        GF2_Span(D, L, span, take, 0)
    return span

## Problem 4
is_it_a_vector_space_1 = True
is_it_a_vector_space_2 = False

## Problem 5
is_it_a_vector_space_3 = True
is_it_a_vector_space_4 = False

## Problem 6
is_it_a_vector_space_5 = True
is_it_a_vector_space_6 = False
