#ifndef NORM_H
#define NORM_H
/**
 * Calculate the norm value of the matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Complex;
class Matrix;

const Complex norm(Matrix &A, int p = 2);

ZMAT_END_NAMESPACE

#endif // NORM_H
