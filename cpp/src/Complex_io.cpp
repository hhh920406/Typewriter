#include <cmath>
#include <cstdio>
#include <iomanip>
#include "Complex.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

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
    if (fabs(num.image()) > ZMAT_EPS)
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

ZMAT_END_NAMESPACE
