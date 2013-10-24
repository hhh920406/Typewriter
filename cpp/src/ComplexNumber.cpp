#include <cmath>
#include <cstdio>
#include <iostream>
#include "ComplexNumber.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

ComplexNumber::ComplexNumber(void)
{
    this->setValue(0.0, 0.0);
}

ComplexNumber::ComplexNumber(const double real)
{
    this->setValue(real, 0.0);
}

ComplexNumber::ComplexNumber(const double real, const double image)
{
    this->setValue(real, image);
}

ComplexNumber::~ComplexNumber()
{
}

inline void ComplexNumber::setReal(const double real)
{
    this->_real = real;
}

inline void ComplexNumber::setImage(const double image)
{
    this->_image = image;
}

inline void ComplexNumber::setValue(const double real, const double image)
{
    this->setReal(real);
    this->setImage(image);
}

inline const double ComplexNumber::getReal(void) const
{
    return this->_real;
}

inline const double ComplexNumber::getImage(void) const
{
    return this->_image;
}

void ComplexNumber::print(void) const
{
    printf("%.3lf ", this->_real);
    if (this->_image <= 0.0)
    {
        printf("- ");
    }
    else
    {
        printf("+ ");
    }
    printf("%.3lf i", fabs(this->_image));
}

void ComplexNumber::printLine(void) const
{
    print();
    putchar('\n');
}

ZMAT_END_NAMESPACE
