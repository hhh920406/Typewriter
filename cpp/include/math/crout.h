#ifndef CROUT_H
#define CROUT_H
/**
 * The Crout LU decompose.
 * All the values in the diagonal of U equals one.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

template<typename T>
struct Crout_Mat
{
    Matrix<T> L;
    Matrix<T> U;
};

template<typename T>
const Crout_Mat<T> crout(Matrix<T> &A)
{
    Crout_Mat<T> cro;
    int n = A.rowNum();
    cro.L.setSize(n, n);
    cro.U.setSize(n, n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            cro.L(j, i) = A(j, i);
            for (int k = 1; k <= i - 1; ++k)
            {
                cro.L(j, i) = cro.L(j, i) - cro.L(j, k) * cro.U(k, i);
            }
            cro.U(i, j) = A(i, j);
            for (int k = 1; k <= i - 1; ++k)
            {
                cro.U(i, j) = cro.U(i, j) - cro.L(i, k) * cro.U(k, j);
            }
            cro.U(i, j) = cro.U(i, j) / cro.L(i, i);
        }
    }
    return cro;
}

ZMAT_END_NAMESPACE

#endif // CROUT_H
