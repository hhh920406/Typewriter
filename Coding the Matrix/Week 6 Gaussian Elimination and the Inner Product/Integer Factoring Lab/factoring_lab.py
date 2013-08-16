from vec import Vec
from GF2 import one
from math import *

from factoring_support import dumb_factor
from factoring_support import intsqrt
from factoring_support import gcd
from factoring_support import primes
from factoring_support import prod

import echelon

## Task 1
def int2GF2(i):
    return one * (i & 1)

## Task 2
def make_Vec(primeset, factors):
    v = Vec(primeset, {})
    for prime, value in factors:
        v[prime] = int2GF2(value)
    return v

## Task 3
def find_candidates(N, primeset):
    roots = []
    rowlist = []
    total = len(primeset) + 1
    count = 0
    x = intsqrt(sqrt(N)) + 2
    while count < total:
        f = x * x - N
        factors = []
        for prime in primeset:
            num = 0
            while f % prime == 0:
                f /= prime
                num += 1
            if num > 0:
                factors.append((prime, num))
        if f == 1:
            roots.append(x)
            rowlist.append(make_Vec(primeset, factors))
            count += 1
        x += 1
    return (roots, rowlist)

## Task 4
def find_a_and_b(v, roots, N):
    alist = [roots[i] for i in v.D if v[i] == one]
    a = prod(alist)
    c = prod([x * x - N for x in alist])
    b = intsqrt(c)
    return (a, b)

## Task 5
smallest_nontrivial_divisor_of_2461799993978700679 = 1230926561
