#ifndef MATRIX_IO_H_INCLUDED
#define MATRIX_IO_H_INCLUDED

#include <iostream>
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

std::istream& operator >>(std::istream &in, Matrix &mat);
std::ostream& operator <<(std::ostream &out, const Matrix &mat);

ZMAT_END_NAMESPACE

#endif // MATRIX_IO_H_INCLUDED
