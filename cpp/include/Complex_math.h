#ifndef COMPLEX_MATH_H_INCLUDED
#define COMPLEX_MATH_H_INCLUDED
/**
 * Provide mathematical operations for complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Complex;

const double abs(const Complex &num);
const double norm(const Complex &num);
const double angle(const Complex &num);
const Complex conjugate(const Complex &num);

ZMAT_END_NAMESPACE

#endif // COMPLEX_MATH_H_INCLUDED
