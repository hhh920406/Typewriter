#ifndef COMPLEXNUMBER_MATH_H_INCLUDED
#define COMPLEXNUMBER_MATH_H_INCLUDED
/**
 * Provide mathematical operations for complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class ComplexNumber;

const double abs(const ComplexNumber &num);
const double norm(const ComplexNumber &num);
const double angle(const ComplexNumber &num);
const ComplexNumber conjugate(const ComplexNumber &num);

ZMAT_END_NAMESPACE

#endif // COMPLEXNUMBER_MATH_H_INCLUDED
