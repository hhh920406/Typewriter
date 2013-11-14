#include "Matrix.h"
#include "math/eye.h"

ZMAT_BEGIN_NAMESPACE

const Matrix eye(const int n)
{
    return eye(n, n);
}

const Matrix eye(const int n, const int m)
{
    Matrix I(n, m);
    int sz = n < m ? n : m;
    for (int i = 1; i <= sz; ++i)
    {
        I(i, i) = 1.0;
    }
    return I;
}

ZMAT_END_NAMESPACE
