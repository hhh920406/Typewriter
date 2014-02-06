#ifndef INV_H
#define INV_H
/**
 * Calculate the inverse matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"
#include "math/doolittle.h"

ZMAT_BEGIN_NAMESPACE

template<typename T>
const Matrix<T> inv(Matrix<T> &X)
{
    Doolittle_Mat<T> doo = doolittle(X);
    Matrix<T> I = eye<T>(X.rowNum());
    Matrix<T> Y(X.rowNum(), X.rowNum());
    for (int j = 1; j <= X.colNum(); ++j)
    {
        for (int i = 1; i <= X.rowNum(); ++i)
        {
            Complex temp = I(i, j);
            for (int k = 1; k < i; ++k)
            {
                temp = temp - Y(k, j) * doo.L(i, k);
            }
            Y(i, j) = temp;
        }
    }
    for (int j = 1; j <= X.colNum(); ++j)
    {
        for (int i = X.rowNum(); i >= 1; --i)
        {
            Complex temp = Y(i, j);
            for (int k = X.rowNum(); k > i; --k)
            {
                temp = temp - Y(k, j) * doo.U(i, k);
            }
            Y(i, j) = temp / doo.U(i, i);
        }
    }
    return Y;
}

ZMAT_END_NAMESPACE

#endif // INV_H
