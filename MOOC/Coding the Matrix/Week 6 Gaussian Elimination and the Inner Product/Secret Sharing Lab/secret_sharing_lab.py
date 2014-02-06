import random
from GF2 import one
from vec import *
from vecutil import *
from independence import is_independent
from itertools import combinations

## Problem 1
def randGF2(): 
    return random.randint(0,1) * one

def randVector():
    return list2vec([randGF2(), randGF2(), randGF2(), randGF2(), randGF2(), randGF2()])

a0 = list2vec([one, one,   0, one,   0, one])
b0 = list2vec([one, one,   0,   0,   0, one])

def choose_secret_vector(s,t):
    while True:
        u = randVector()
        if a0 * u == s and b0 * u == t:
            return u

## Problem 2
secret_a0 = list2vec([one, one, 0, one, 0, one])
secret_b0 = list2vec([one, one, 0, 0, 0, one])

def choose_secret():
    while True:
        secret_a1 = randVector()
        secret_b1 = randVector()
        secret_a2 = randVector()
        secret_b2 = randVector()
        secret_a3 = randVector()
        secret_b3 = randVector()
        secret_a4 = randVector()
        secret_b4 = randVector()
        vecs = [(secret_a0, secret_b0),(secret_a1,secret_b1),(secret_a2,secret_b2),(secret_a3,secret_b3),(secret_a4,secret_b4)]
        if all(is_independent(list(sum(x,()))) for x in combinations(vecs,3)):
            return vecs

vecs = choose_secret()
secret_a1, secret_b1 = vecs[1]
secret_a2, secret_b2 = vecs[2]
secret_a3, secret_b3 = vecs[3]
secret_a4, secret_b4 = vecs[4]
