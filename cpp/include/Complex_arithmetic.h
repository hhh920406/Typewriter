#ifndef COMPLEX_ARITHMETIC_H_INCLUDED
#define COMPLEX_ARITHMETIC_H_INCLUDED
/**
 * Provide arithmetic operations for complex number.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"

ZMAT_BEGIN_NAMESPACE

class Complex;

const Complex operator +(const Complex &a, const Complex &b);
const Complex operator -(const Complex &a, const Complex &b);
const Complex operator *(const Complex &a, const Complex &b);
const Complex operator /(const Complex &a, const Complex &b);
const Complex operator /(const Complex &a, const double b);

bool operator ==(const Complex &a, const Complex &b);

ZMAT_END_NAMESPACE

#endif // COMPLEX_ARITHMETIC_H_INCLUDED
