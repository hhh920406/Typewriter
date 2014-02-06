from random import randint
from dictutil import *

## Task 1
def movie_review(name):
    review_options = ["See it!", "A gem!", "Ideological claptrap!"]
    return review_options[randint(0, 2)]

## Tasks 2 and 3 are in dictutil.py

## Task 4    
def makeInverseIndex(strlist):
    words = []
    for document in strlist:
        words += document.split()
    inverse = {x:set() for (k, x) in list(enumerate(words))}
    for i in range(len(strlist)):
        words = strlist[i].split()
        for word in words:
            inverse[word].add(i)
    return inverse

## Task 5
def orSearch(inverseIndex, query):
    documents = set()
    for word in query:
        documents |= inverseIndex[word]
    return documents

## Task 6
def andSearch(inverseIndex, query):
    documents = set(range(len(inverseIndex)))
    for word in query:
        documents &= inverseIndex[word]
    return documents
