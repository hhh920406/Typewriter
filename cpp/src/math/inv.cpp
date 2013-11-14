#include "Matrix.h"
#include "math/doolittle.h"
#include "math/inv.h"

ZMAT_BEGIN_NAMESPACE

const Matrix inv(Matrix &X)
{
    Doolittle_Mat doo = doolittle(X);
}

ZMAT_END_NAMESPACE
