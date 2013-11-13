#include <cmath>
#include "ComplexNumber.h"
#include "ComplexNumber_arithmetic.h"
#include "SolidMatrix.h"
#include "SolidMatrix_arithmetic.h"

ZMAT_BEGIN_NAMESPACE

const SolidMatrix operator +(const SolidMatrix &a, const SolidMatrix &b) {
    SolidMatrix c(a.rowNum(), a.colNum());
    for (int i = 1; i <= a.rowNum(); ++i) {
        for (int j = 1; j <= a.colNum(); ++j) {
            c.setData(i, j, a.data(i, j) + b.data(i, j));
        }
    }
    return c;
}

const SolidMatrix operator -(const SolidMatrix &a, const SolidMatrix &b) {
    SolidMatrix c(a.rowNum(), a.colNum());
    for (int i = 1; i <= a.rowNum(); ++i) {
        for (int j = 1; j <= a.colNum(); ++j) {
            c.setData(i, j, a.data(i, j) - b.data(i, j));
        }
    }
    return c;
}

const SolidMatrix operator *(const SolidMatrix &a, const SolidMatrix &b) {
    SolidMatrix c(a.rowNum(), b.colNum());
    for (int i = 1; i <= a.rowNum(); ++i) {
        for (int j = 1; j <= b.colNum(); ++j) {
            c.setData(i, j, 0.0);
            for (int k = 1; k <= a.colNum(); ++k) {
                c.setData(i, j, a.data(i, k) * b.data(k, j) + c.data(i, j));
            }
        }
    }
    return c;
}

const bool operator ==(const SolidMatrix &a, const SolidMatrix &b) {
    for (int i = 1; i <= a.rowNum(); ++i) {
        for (int j = 1; j <= a.colNum(); ++j) {
            if (!(a.data(i, j) == b.data(i, j))) {
                return false;
            }
        }
    }
    return true;
}

ZMAT_END_NAMESPACE
