def getitem(v,d):
    "Returns the value of entry d in v"
    assert d in v.D
    return v.f[d] if d in v.f else 0

def setitem(v,d,val):
    "Set the element of v with label d to be val"
    assert d in v.D
    v.f[d] = val

def equal(u,v):
    "Returns true iff u is equal to v"
    assert u.D == v.D
    for x in u.D:
        if getitem(u, x) != getitem(v, x):
            return False
    return True

def add(u,v):
    "Returns the sum of the two vectors"
    assert u.D == v.D
    values = {}
    for x in u.D:
        values[x] = getitem(u,x) + getitem(v, x)
    return Vec(u.D, values)

def dot(u,v):
    "Returns the dot product of the two vectors"
    assert u.D == v.D
    sum = 0
    for x in u.D:
        sum += getitem(u,x) * getitem(v, x)
    return sum

def scalar_mul(v, alpha):
    "Returns the scalar-vector product alpha times v"
    vec = Vec(v.D, {})
    for x in v.D:
        vec.f[x] = getitem(v, x) * alpha
    return vec

def neg(v):
    "Returns the negation of a vector"
    return scalar_mul(v, -1)
