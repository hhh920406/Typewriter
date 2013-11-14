#ifndef EYE_H
#define EYE_H

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

const Matrix eye(const int n = 1);
const Matrix eye(const int n, const int m);

ZMAT_END_NAMESPACE

#endif // EYE_H
