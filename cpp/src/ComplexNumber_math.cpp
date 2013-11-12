#include <cmath>
#include "ComplexNumber.h"
#include "ComplexNumber_math.h"

ZMAT_BEGIN_NAMESPACE

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

ZMAT_END_NAMESPACE
