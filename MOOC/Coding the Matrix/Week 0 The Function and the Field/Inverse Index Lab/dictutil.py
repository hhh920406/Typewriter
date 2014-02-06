## Task 2
def dict2list(dct, keylist): return [ dct[x] for x in keylist ]

def list2dict(L, keylist): return { keylist[x]:L[x] for x in range(len(L)) }

## Task 3
def listrange2dict(L):
    return list2dict(L, range(len(L)))

