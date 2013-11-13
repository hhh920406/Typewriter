#include <cmath>
#include "Complex.h"

ZMAT_BEGIN_NAMESPACE

const Complex operator +(const Complex &a, const Complex &b) {
    return Complex(a.real() + b.real(), a.image() + b.image());
}

const Complex operator -(const Complex &a, const Complex &b) {
    return Complex(a.real() - b.real(), a.image() - b.image());
}

const Complex operator *(const Complex &a, const Complex &b) {
    return Complex(a.real() * b.real() - a.image() * b.image(),
                         a.real() * b.image() + a.image() * b.real());
}

const Complex operator /(const Complex &a, const Complex &b) {
    return a * conjugate(b) / (b.real() * b.real() + b.image() * b.image());
}

const Complex operator /(const Complex &a, const double b) {
    return Complex(a.real() / b, a.image() / b);
}

bool operator ==(const Complex &a, const Complex &b) {
    return fabs(a.real() - b.real()) < ZMAT_EPS && fabs(a.image() - b.image()) < ZMAT_EPS;
}

ZMAT_END_NAMESPACE
