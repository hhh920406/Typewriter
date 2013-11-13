#ifndef SOLIDMATRIX_IO_H_INCLUDED
#define SOLIDMATRIX_IO_H_INCLUDED

#include <iostream>
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class SolidMatrix;

std::istream& operator >>(std::istream &in, SolidMatrix &mat);
std::ostream& operator <<(std::ostream &out, const SolidMatrix &mat);

ZMAT_END_NAMESPACE

#endif // SOLIDMATRIX_IO_H_INCLUDED
