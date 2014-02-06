#ifndef COMPLEX_H
#define COMPLEX_H
/**
 * The basic defination of complex number.
 * The number contains real part and image part.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "ZMat.h"
#include <iostream>

ZMAT_BEGIN_NAMESPACE

class Complex
{
public:
    Complex();
    Complex(const double real);
    Complex(const double real, const double image);
    virtual ~Complex();

    void setReal(const double real);
    void setImage(const double image);
    void setValue(const double real, const double image);
    const double real() const;
    const double image() const;

protected:
    double _real;
    double _image;
};

std::istream& operator >>(std::istream &in, Complex &num);
std::ostream& operator <<(std::ostream &out, const Complex &num);

const Complex operator +(const Complex &a, const Complex &b);
const Complex operator -(const Complex &a, const Complex &b);
const Complex operator *(const Complex &a, const Complex &b);
const Complex operator /(const Complex &a, const Complex &b);
const Complex operator /(const Complex &a, const double b);

bool operator ==(const Complex &a, const Complex &b);

const double abs(const Complex &num);
const double norm(const Complex &num);
const double angle(const Complex &num);
const Complex conjugate(const Complex &num);

ZMAT_END_NAMESPACE

#endif // COMPLEX_H
