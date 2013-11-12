#include <cmath>
#include "ComplexNumber.h"
#include "ComplexNumber_math.h"

ZMAT_BEGIN_NAMESPACE

const double abs(const ComplexNumber &num) {
    return sqrt(num.image() * num.image() + num.real() * num.real());
}

const double norm(const ComplexNumber &num) {
    return abs(num);
}

const double angle(const ComplexNumber &num) {
    return atan2(num.image(), num.real());
}

const ComplexNumber conjugate(const ComplexNumber &num) {
    return ComplexNumber(num.real(), - num.image());
}

ZMAT_END_NAMESPACE
