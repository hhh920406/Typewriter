#ifndef DOOLITTLE_H
#define DOOLITTLE_H
/**
 * The Doolittle LU decompose.
 * All the values in the diagonal of L equals one.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

template<typename T>
struct Doolittle_Mat
{
    Matrix<T> L;
    Matrix<T> U;
};

template<typename T>
const Doolittle_Mat<T> doolittle(Matrix<T> &A)
{
    Doolittle_Mat<T> doo;
    int n = A.rowNum();
    doo.L.setSize(n, n);
    doo.U.setSize(n, n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            doo.U(i, j) = A(i, j);
            for (int k = 1; k <= i - 1; ++k)
            {
                doo.U(i, j) = doo.U(i, j) - doo.L(i, k) * doo.U(k, j);
            }
            doo.L(j, i) = A(j, i);
            for (int k = 1; k <= i - 1; ++k)
            {
                doo.L(j, i) = doo.L(j, i) - doo.L(j, k) * doo.U(k, i);
            }
            doo.L(j, i) = doo.L(j, i) / doo.U(i, i);
        }
    }
    return doo;
}

ZMAT_END_NAMESPACE

#endif // DOOLITTLE_H
