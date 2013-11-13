#include "SolidMatrix.h"
#include "SolidMatrix_io.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

istream& operator >>(istream &in, SolidMatrix &mat) {
    int r, c;
    double temp;
    in >> r >> c;
    mat.setSize(r, c);
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            in >> temp;
            mat.setData(i, j, temp);
        }
    }
    return in;
}

ostream& operator <<(ostream &out, const SolidMatrix &mat) {
    out << "[" << mat.rowNum() << ", " << mat.colNum() << "]" << endl;
    for (int i = 1; i <= mat.rowNum(); ++i) {
        for (int j = 1; j <= mat.colNum(); ++j) {
            out << mat.data(i, j) << '\t';
        }
        out << endl;
    }
    return out;
}

ZMAT_END_NAMESPACE
