#include <cmath>
#include <cstdio>
#include <iostream>
#include "ComplexNumber.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

ComplexNumber::ComplexNumber() {
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

void ComplexNumber::setReal(const double real) {
    this->_real = real;
}

void ComplexNumber::setImage(const double image) {
    this->_image = image;
}

void ComplexNumber::setValue(const double real, const double image) {
    this->setReal(real);
    this->setImage(image);
}

const double ComplexNumber::real() const {
    return this->_real;
}

const double ComplexNumber::image() const {
    return this->_image;
}

ZMAT_END_NAMESPACE
