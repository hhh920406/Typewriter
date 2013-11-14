#ifndef INV_H
#define INV_H
/**
 * Calculate the inverse matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

const Matrix inv(Matrix &X);

ZMAT_END_NAMESPACE

#endif // INV_H
