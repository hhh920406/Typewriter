#ifndef DOOLITTLE_H
#define DOOLITTLE_H

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

struct Doolittle_Mat {
    Matrix L;
    Matrix U;
};

const Doolittle_Mat doolittle(Matrix &A);

ZMAT_END_NAMESPACE

#endif // DOOLITTLE_H
