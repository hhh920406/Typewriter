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

istream& operator >>(istream &in, Complex &num)
{
    double real, image;
    in >> real >> image;
    num.setValue(real, image);
    return in;
}

ostream& operator <<(ostream &out, const Complex &num)
{
    out << num.real();
    if (abs(num.image()) > ZMAT_EPS)
    {
        if (num.image() <= 0.0)
        {
            out << " - ";
        }
        else
        {
            out << " + ";
        }
        out << num.image() << " i";
    }
    return out;
}

const Complex operator +(const Complex &a, const Complex &b)
{
    return Complex(a.real() + b.real(), a.image() + b.image());
}

const Complex operator -(const Complex &a, const Complex &b)
{
    return Complex(a.real() - b.real(), a.image() - b.image());
}

const Complex operator *(const Complex &a, const Complex &b)
{
    return Complex(a.real() * b.real() - a.image() * b.image(),
                   a.real() * b.image() + a.image() * b.real());
}

const Complex operator /(const Complex &a, const Complex &b)
{
    return a * conjugate(b) / (b.real() * b.real() + b.image() * b.image());
}

const Complex operator /(const Complex &a, const double b)
{
    return Complex(a.real() / b, a.image() / b);
}

bool operator ==(const Complex &a, const Complex &b)
{
    return abs(a.real() - b.real()) < ZMAT_EPS && abs(a.image() - b.image()) < ZMAT_EPS;
}

const double abs(const Complex &num)
{
    return sqrt(num.image() * num.image() + num.real() * num.real());
}

const double norm(const Complex &num)
{
    return abs(num);
}

const double angle(const Complex &num)
{
    return atan2(num.image(), num.real());
}

const Complex conjugate(const Complex &num)
{
    return Complex(num.real(), - num.image());
}

ZMAT_END_NAMESPACE
