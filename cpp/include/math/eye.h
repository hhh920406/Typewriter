#ifndef EYE_H
#define EYE_H
/**
 * Create a identity matrix with values on main diagonal equals one.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Matrix;

const Matrix eye(const int n = 1);
const Matrix eye(const int n, const int m);

ZMAT_END_NAMESPACE

#endif // EYE_H
