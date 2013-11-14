#ifndef LDU_H
#define LDU_H
/**
 * The LDU decompose.
 * All the values in the diagonal of L and U equals one.
 * D is a diagonal matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

template<typename T>
struct LDU_Mat
{
    Matrix<T> L;
    Matrix<T> D;
    Matrix<T> U;
};

template<typename T>
const LDU_Mat<T> ldu(Matrix<T> &A)
{
    LDU_Mat<T> ldu;
    int n = A.rowNum();
    ldu.L.setSize(n, n);
    ldu.D.setSize(n, n);
    ldu.U.setSize(n, n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i; j <= n; ++j)
        {
            ldu.U(i, j) = A(i, j);
            for (int k = 1; k <= i - 1; ++k)
            {
                ldu.U(i, j) = ldu.U(i, j) - ldu.L(i, k) * ldu.U(k, j);
            }
            ldu.L(j, i) = A(j, i);
            for (int k = 1; k <= i - 1; ++k)
            {
                ldu.L(j, i) = ldu.L(j, i) - ldu.L(j, k) * ldu.U(k, i);
            }
            ldu.L(j, i) = ldu.L(j, i) / ldu.U(i, i);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        ldu.D(i, i) = ldu.U(i, i);
        for (int j = i; j <= n; ++j)
        {
            ldu.U(i, j) = ldu.U(i, j) / ldu.D(i, i);
        }
    }
    return ldu;
}

ZMAT_END_NAMESPACE

#endif // LDU_H
