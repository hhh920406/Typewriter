#ifndef INV_H
#define INV_H

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

const Matrix inv(Matrix &X);

ZMAT_END_NAMESPACE

#endif // INV_H
