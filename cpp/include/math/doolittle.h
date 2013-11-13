#ifndef DOOLITTLE_H
#define DOOLITTLE_H

#include "ZMat.h"
#include "SolidMatrix.h"

ZMAT_BEGIN_NAMESPACE

struct Doolittle_Mat {
    SolidMatrix L;
    SolidMatrix U;
};

const Doolittle_Mat doolittle(SolidMatrix &A);

ZMAT_END_NAMESPACE

#endif // DOOLITTLE_H
