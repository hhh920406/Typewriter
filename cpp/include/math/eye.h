#ifndef EYE_H
#define EYE_H
/**
 * Create a identity matrix with values on main diagonal equals one.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

template<typename T>
const Matrix<T> eye(const int n, const int m)
{
    Matrix<T> I(n, m);
    int sz = n < m ? n : m;
    for (int i = 1; i <= sz; ++i)
    {
        I(i, i) = 1.0;
    }
    return I;
}

template<typename T>
const Matrix<T> eye(const int n = 1)
{
    return eye<T>(n, n);
}

ZMAT_END_NAMESPACE

#endif // EYE_H
