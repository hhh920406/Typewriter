#include <cmath>
#include "Complex.h"

ZMAT_BEGIN_NAMESPACE

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
