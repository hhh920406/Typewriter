#include <cmath>
#include <cstdio>
#include <iostream>
#include "Complex.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

Complex::Complex()
{
    this->setValue(0.0, 0.0);
}

Complex::Complex(const double real)
{
    this->setValue(real, 0.0);
}

Complex::Complex(const double real, const double image)
{
    this->setValue(real, image);
}

Complex::~Complex()
{
}

void Complex::setReal(const double real)
{
    this->_real = real;
}

void Complex::setImage(const double image)
{
    this->_image = image;
}

void Complex::setValue(const double real, const double image)
{
    this->setReal(real);
    this->setImage(image);
}

const double Complex::real() const
{
    return this->_real;
}

const double Complex::image() const
{
    return this->_image;
}

ZMAT_END_NAMESPACE
