from vec import Vec

def getitem(M, k):
    assert k[0] in M.D[0] and k[1] in M.D[1]
    return M.f[k] if k in M.f else 0

def setitem(M, k, val):
    assert k[0] in M.D[0] and k[1] in M.D[1]
    M.f[k] = val

def add(A, B):
    assert A.D == B.D
    C = Mat(A.D, {})
    for i in A.D[0]:
        for j in A.D[1]:
            C[(i, j)] = A[(i, j)] + B[(i, j)]
    return C

def scalar_mul(M, alpha):
    N = Mat(M.D, {})
    for i in M.D[0]:
        for j in M.D[1]:
            N[(i, j)] = M[(i, j)] * alpha
    return N

def equal(A, B):
    assert A.D == B.D
    for i in A.D[0]:
        for j in A.D[1]:
            if A[(i, j)] != B[(i, j)]:
                return False
    return True

def transpose(M):
    N = Mat((M.D[1], M.D[0]), {})
    for i in M.D[0]:
        for j in M.D[1]:
            N[(j, i)] = M[(i, j)]
    return N

def vector_matrix_mul(v, M):
    assert M.D[0] == v.D
    n = Vec(M.D[1], {})
    for j in M.D[1]:
        temp = 0
        for i in M.D[0]:
            temp += v[i] * M[(i, j)]
        n[j] = temp
    return n

def matrix_vector_mul(M, v):
    assert M.D[1] == v.D
    n = Vec(M.D[0], {})
    for i in M.D[0]:
        temp = 0
        for j in M.D[1]:
            temp += v[j] * M[(i, j)]
        n[i] = temp
    return n

def matrix_matrix_mul(A, B):
    assert A.D[1] == B.D[0]
    C = Mat((A.D[0], B.D[1]), {})
    for i in A.D[0]:
        for j in B.D[1]:
            temp = 0
            for k in A.D[1]:
                temp += A[(i, k)] * B[(k, j)]
            if type(temp) == float:
                if abs(temp) > 1e-14:
                    C[(i, j)] = temp
            else:
                C[(i, j)] = temp
    return C

################################################################################

class Mat:
    def __init__(self, labels, function):
        self.D = labels
        self.f = function

    __getitem__ = getitem
    __setitem__ = setitem
    transpose = transpose

    def __neg__(self):
        return (-1)*self

    def __mul__(self,other):
        if Mat == type(other):
            return matrix_matrix_mul(self,other)
        elif Vec == type(other):
            return matrix_vector_mul(self,other)
        else:
            return scalar_mul(self,other)

    def __rmul__(self, other):
        if Mat == type(other):
            return matrix_matrix_mul(other, self)
        elif Vec == type(other):
            return vector_matrix_mul(other, self)
        else:
            return scalar_mul(self, other)

    __add__ = add

    def __sub__(a,b):
        return a+(-b)

    __eq__ = equal

    def copy(self):
        return Mat(self.D, self.f.copy())

    def __str__(M, rows=None, cols=None):
        "string representation for print()"
        if rows == None:
            try:
                rows = sorted(M.D[0])
            except TypeError:
                rows = sorted(M.D[0], key=hash)
        if cols == None:
            try:
                cols = sorted(M.D[1])
            except TypeError:
                cols = sorted(M.D[1], key=hash)
        separator = ' | '
        numdec = 3
        pre = 1+max([len(str(r)) for r in rows])
        colw = {col:(1+max([len(str(col))] + [len('{0:.{1}G}'.format(M[row,col],numdec)) if isinstance(M[row,col], int) or isinstance(M[row,col], float) else len(str(M[row,col])) for row in rows])) for col in cols}
        s1 = ' '*(1+ pre + len(separator))
        s2 = ''.join(['{0:>{1}}'.format(c,colw[c]) for c in cols])
        s3 = ' '*(pre+len(separator)) + '-'*(sum(list(colw.values())) + 1)
        s4 = ''.join(['{0:>{1}} {2}'.format(r, pre,separator)+''.join(['{0:>{1}.{2}G}'.format(M[r,c],colw[c],numdec) if isinstance(M[r,c], int) or isinstance(M[r,c], float) else '{0:>{1}}'.format(M[r,c], colw[c]) for c in cols])+'\n' for r in rows])
        return '\n' + s1 + s2 + '\n' + s3 + '\n' + s4

    def pp(self, rows, cols):
        print(self.__str__(rows, cols))

    def __repr__(self):
        "evaluatable representation"
        return "Mat(" + str(self.D) +", " + str(self.f) + ")"
