#ifndef SOLIDMATRIX_ARITHMETIC_H_INCLUDED
#define SOLIDMATRIX_ARITHMETIC_H_INCLUDED

#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class SolidMatrix;

const SolidMatrix operator +(const SolidMatrix &a, const SolidMatrix &b);
const SolidMatrix operator -(const SolidMatrix &a, const SolidMatrix &b);
const SolidMatrix operator *(const SolidMatrix &a, const SolidMatrix &b);

const bool operator ==(const SolidMatrix &a, const SolidMatrix &b);

ZMAT_END_NAMESPACE

#endif // SOLIDMATRIX_ARITHMETIC_H_INCLUDED
