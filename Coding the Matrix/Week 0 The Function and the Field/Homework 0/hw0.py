from GF2 import one

## Problem 1
def myFilter(L, num):
    return [x for x in L if x % num != 0]

## Problem 2
def myLists(L):
    return [[y + 1 for y in range(x)] for x in L]

## Problem 3
def myFunctionComposition(f, g): 
    return {k:g[v] for (k, v) in f.items()}

## Problem 4
# Please only enter your numerical solution.

complex_addition_a = (3 + 1j) + (2 + 2j) 
complex_addition_b = (-1 + 2j) + (1 - 1j)
complex_addition_c = (2 + 0j) + (-3 + .001j)
complex_addition_d = 4 * (0 + 2j) + (.001 + 1j)

## Problem 5
GF2_sum_1 = 1
GF2_sum_2 = one * one + 0 * one + 0 * 0 + one * one
GF2_sum_3 = (one + one + one) * (one + one + one + one)


## Problem 6
def mySum(L):
    return sum(L)

## Problem 7
def myProduct(L):
    product = 1
    for i in L:
        product *= i
    return product

## Problem 8
def myMin(L):
    mini = L[0]
    for i in L:
        mini = min(mini, i)
    return mini

## Problem 9
def myConcat(L):
    cat = ""
    for str in L:
        cat += str
    return cat

## Problem 10
def myUnion(L): 
    union = set()
    for s in L:
        union |= s
    return union

