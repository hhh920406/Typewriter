#include "Matrix.h"
#include "math/ldu.h"

ZMAT_BEGIN_NAMESPACE

const LDU_Mat ldu(Matrix &A)
{
    LDU_Mat ldu;
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
