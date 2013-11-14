#ifndef LDU_H
#define LDU_H

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

struct LDU_Mat
{
    Matrix L;
    Matrix D;
    Matrix U;
};

const LDU_Mat ldu(Matrix &A);

ZMAT_END_NAMESPACE

#endif // LDU_H
