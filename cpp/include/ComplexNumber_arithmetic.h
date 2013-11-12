#ifndef COMPLEXNUMBER_ARITHMETIC_H_INCLUDED
#define COMPLEXNUMBER_ARITHMETIC_H_INCLUDED
/**
 * Provide arithmetic operations for complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class ComplexNumber;

const ComplexNumber operator +(const ComplexNumber &a, const ComplexNumber &b);
const ComplexNumber operator -(const ComplexNumber &a, const ComplexNumber &b);
const ComplexNumber operator *(const ComplexNumber &a, const ComplexNumber &b);
const ComplexNumber operator /(const ComplexNumber &a, const ComplexNumber &b);

bool operator ==(const ComplexNumber &a, const ComplexNumber &b);

ZMAT_END_NAMESPACE

#endif // COMPLEXNUMBER_ARITHMETIC_H_INCLUDED
