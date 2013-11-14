#include "Matrix.h"
#include "math/doolittle.h"
#include "math/eye.h"
#include "math/inv.h"

ZMAT_BEGIN_NAMESPACE

const Matrix inv(Matrix &X)
{
    Doolittle_Mat doo = doolittle(X);
    Matrix I = eye(X.rowNum());
    Matrix Y(X.rowNum(), X.rowNum());
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
