#include <cmath>
#include "ComplexNumber.h"
#include "ComplexNumber_math.h"
#include "ComplexNumber_arithmetic.h"

ZMAT_BEGIN_NAMESPACE

const ComplexNumber operator +(const ComplexNumber &a, const ComplexNumber &b) {
    return ComplexNumber(a.real() + b.real(), a.image() + b.image());
}

const ComplexNumber operator -(const ComplexNumber &a, const ComplexNumber &b) {
    return ComplexNumber(a.real() - b.real(), a.image() - b.image());
}

const ComplexNumber operator *(const ComplexNumber &a, const ComplexNumber &b) {
    return ComplexNumber(a.real() * b.real() - a.image() * b.image(),
                         a.real() * b.image() + a.image() * b.real());
}

const ComplexNumber operator /(const ComplexNumber &a, const ComplexNumber &b) {
    return a * conjugate(b) / (b.real() * b.real() + b.image() * b.image());
}

const ComplexNumber operator /(const ComplexNumber &a, const double b) {
    return ComplexNumber(a.real() / b, a.image() / b);
}

bool operator ==(const ComplexNumber &a, const ComplexNumber &b) {
    return fabs(a.real() - b.real()) < ZMAT_EPS && fabs(a.image() - b.image()) < ZMAT_EPS;
}

ZMAT_END_NAMESPACE
