#ifndef CROUT_H
#define CROUT_H
/**
 * The Crout LU decompose.
 * All the values in the diagonal of U equals one.
 * @author ZHG <CyberZHG@gmail.com>
 */
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
