from mat import *
from vec import *
from cancer_data import *

## Task 1 ##
def signum(u):
    return Vec(u.D, {k: (1 if u[k] >= 0 else -1) for k in u.D})

## Task 2 ##
def fraction_wrong(A, b, w):
    v = signum(A * w)
    return 1.0 * len([x for x in b.D if b[x] != v[x]]) / len(b.D)

## Task 3 ##
def loss(A, b, w):
    v = A * w
    return sum([(b[k] - v[k]) ** 2 for k in b.D])

## Task 4 ##
def find_grad(A, b, w):
    return 2 * (A * w - b) * A

## Task 5 ##
def gradient_descent_step(A, b, w, sigma):
    return w - sigma * find_grad(A, b, w)

