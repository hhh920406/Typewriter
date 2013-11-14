#ifndef LDU_H
#define LDU_H
/**
 * The LDU decompose.
 * All the values in the diagonal of L and U equals one.
 * D is a diagonal matrix.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

struct LDU_Mat
{
    Matrix L;
    Matrix D;
    Matrix U;
};

const LDU_Mat ldu(Matrix &A);

ZMAT_END_NAMESPACE

#endif // LDU_H
