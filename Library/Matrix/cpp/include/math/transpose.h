#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/**
 * Calculate the transpose matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

template<typename T>
const Matrix<T> transpose(Matrix<T> &A)
{
    Matrix<T> B(A.colNum(), A.rowNum());
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

#endif // TRANSPOSE_H
