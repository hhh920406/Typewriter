#include "Matrix.h"
#include "math/transpose.h"

ZMAT_BEGIN_NAMESPACE

const Matrix transpose(Matrix &A)
{
    Matrix B(A.colNum(), A.rowNum());
    for (int i = 1; i <= A.rowNum(); ++i)
    {
        for (int j = 1; j <= A.colNum(); ++j)
        {
            B(j, i) = A(i, j);
        }
    }
    return B;
}

ZMAT_END_NAMESPACE
