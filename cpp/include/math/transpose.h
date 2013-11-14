#ifndef TRANSPOSE_H
#define TRANSPOSE_H
/**
 * Calculate the transpose matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

const Matrix transpose(Matrix &A);

ZMAT_END_NAMESPACE

#endif // TRANSPOSE_H
