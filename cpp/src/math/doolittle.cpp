#include "math/doolittle.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

const Doolittle_Mat doolittle(SolidMatrix &A) {
    Doolittle_Mat doo;
    int n = A.rowNum();
    doo.L.setSize(n, n);
    doo.U.setSize(n, n);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            doo.U(i, j) = A(i, j);
            for (int k = 1; k <= i - 1; ++k) {
                doo.U(i, j) = doo.U(i, j) - doo.L(i, k) * doo.U(k, j);
            }
            doo.L(j, i) = A(j, i);
            for (int k = 1; k <= i - 1; ++k) {
                doo.L(j, i) = doo.L(j, i) - doo.L(j, k) * doo.U(k, i);
            }
            doo.L(j, i) = doo.L(j, i) / doo.U(i, i);
        }
    }
    return doo;
}

ZMAT_END_NAMESPACE
