#ifndef CROUT_H
#define CROUT_H

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

struct Crout_Mat
{
    Matrix L;
    Matrix U;
};

const Crout_Mat crout(Matrix &A);

ZMAT_END_NAMESPACE

#endif // CROUT_H
