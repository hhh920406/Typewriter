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

void ComplexNumber::print(void) const {
    printf("%.3lf ", this->_real);
    if (this->_image <= 0.0) {
        printf("- ");
    } else {
        printf("+ ");
    }
    printf("%.3lf i", fabs(this->_image));
}

void ComplexNumber::printLine(void) const {
    print();
    putchar('\n');
}

inline const double ComplexNumber::abs(void) const {
    return sqrt(this->image() * this->image() + this->real() * this->real());
}

inline const double ComplexNumber::norm(void) const {
    return abs();
}

inline const double ComplexNumber::angle(void) const {
    return atan2(this->image(), this->real());
}

inline const ComplexNumber ComplexNumber::conjugate(void) const {
    return ComplexNumber(this->real(), - this->image());
}

inline ComplexNumber& ComplexNumber::operator +=(const double value) {
    this->setReal(this->real() + value);
    return *this;
}

inline ComplexNumber& ComplexNumber::operator -=(const double value) {
    this->setReal(this->real() - value);
    return *this;
}

inline ComplexNumber& ComplexNumber::operator *=(const double value) {
    this->setReal(this->real() * value);
    this->setImage(this->image() * value);
    return *this;
}

inline ComplexNumber& ComplexNumber::operator /=(const double value) {
    this->setReal(this->real() / value);
    this->setImage(this->image() / value);
    return *this;
}

inline ComplexNumber& ComplexNumber::operator +=(const ComplexNumber &cn) {
    this->setReal(this->real() + cn.real());
    this->setImage(this->image() + cn.image());
    return *this;
}

inline ComplexNumber& ComplexNumber::operator -=(const ComplexNumber &cn) {
    this->setReal(this->real() - cn.real());
    this->setImage(this->image() - cn.image());
    return *this;
}

inline ComplexNumber& ComplexNumber::operator *=(const ComplexNumber &cn) {
    this->setReal(this->real() * cn.real() - this->image() * cn.image());
    this->setImage(this->real() * cn.image() + this->image() * cn.real());
    return *this;
}

inline ComplexNumber& ComplexNumber::operator /=(const ComplexNumber &cn) {
    ComplexNumber num = ((*this) * cn.conjugate()) / cn.norm();
    this->setValue(num.real(), num.image());
    return *this;
}

inline const ComplexNumber operator +(const double a, const ComplexNumber &b) {
    return ComplexNumber(a + b.real(), b.image());
}

inline const ComplexNumber operator -(const double a, const ComplexNumber &b) {
    return ComplexNumber(a - b.real(), b.image());
}

inline const ComplexNumber operator *(const double a, const ComplexNumber &b) {
    return ComplexNumber(a * b.real(), a * b.image());
}

inline const ComplexNumber operator /(const double a, const ComplexNumber &b) {
    return ComplexNumber(a / b.real(), a / b.image());
}

inline const ComplexNumber operator +(const ComplexNumber &a, const double b) {
    return ComplexNumber(a.real() + b, a.image());
}

inline const ComplexNumber operator -(const ComplexNumber &a, const double b) {
    return ComplexNumber(a.real() - b, a.image());
}

inline const ComplexNumber operator *(const ComplexNumber &a, const double b) {
    return ComplexNumber(a.real() * b, a.image() * b);
}

inline const ComplexNumber operator /(const ComplexNumber &a, const double b) {
    return ComplexNumber(a.real() / b, a.image() / b);
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
    return a * b.conjugate() / b.norm();
}

inline bool ComplexNumber::operator ==(const ComplexNumber &cn) {
    return fabs(this->real() - cn.real()) < ZMAT_EPS &&
           fabs(this->image() - cn.image()) < ZMAT_EPS;
}

ZMAT_END_NAMESPACE
