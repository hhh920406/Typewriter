#include <cmath>
#include <cstdio>
#include <iostream>
#include "ComplexNumber.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

ComplexNumber::ComplexNumber(void) {
    this->setValue(0.0, 0.0);
}

ComplexNumber::ComplexNumber(const double real) {
    this->setValue(real, 0.0);
}

ComplexNumber::ComplexNumber(const double real, const double image) {
    this->setValue(real, image);
}

ComplexNumber::~ComplexNumber() {
}

inline void ComplexNumber::setReal(const double real) {
    this->_real = real;
}

inline void ComplexNumber::setImage(const double image) {
    this->_image = image;
}

inline void ComplexNumber::setValue(const double real, const double image) {
    this->setReal(real);
    this->setImage(image);
}

inline const double ComplexNumber::real(void) const {
    return this->_real;
}

inline const double ComplexNumber::image(void) const {
    return this->_image;
}

ostream& operator <<(ostream& out, const ComplexNumber &num) {
    printf("%.3lf ", num.real());
    if (num.image() <= 0.0) {
        printf("- ");
    } else {
        printf("+ ");
    }
    printf("%.3lf i", fabs(num.image()));
    return out;
}

inline const double abs(const ComplexNumber &num) {
    return sqrt(num.image() * num.image() + num.real() * num.real());
}

inline const double norm(const ComplexNumber &num) {
    return abs(num);
}

inline const double angle(const ComplexNumber &num) {
    return atan2(num.image(), num.real());
}

inline const ComplexNumber conjugate(const ComplexNumber &num) {
    return ComplexNumber(num.real(), - num.image());
}

inline const ComplexNumber operator +(const ComplexNumber &a, const ComplexNumber &b) {
    return ComplexNumber(a.real() + b.real(), a.image() + b.image());
}

inline const ComplexNumber operator -(const ComplexNumber &a, const ComplexNumber &b) {
    return ComplexNumber(a.real() - b.real(), a.image() - b.image());
}

inline const ComplexNumber operator *(const ComplexNumber &a, const ComplexNumber &b) {
    return ComplexNumber(a.real() * b.real() - a.image() * b.image(),
                         a.real() * b.image() + a.image() * b.real());
}

inline const ComplexNumber operator /(const ComplexNumber &a, const ComplexNumber &b) {
    return a * conjugate(b) / norm(b);
}

inline bool operator ==(const ComplexNumber &a, const ComplexNumber &b) {
    return fabs(a.real() - b.real()) < ZMAT_EPS && fabs(a.image() - b.image()) < ZMAT_EPS;
}

ZMAT_END_NAMESPACE
