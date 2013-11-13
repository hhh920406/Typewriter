#include <cmath>
#include <cstdio>
#include <iomanip>
#include "ComplexNumber.h"
#include "ComplexNumber_io.h"
using namespace std;

ZMAT_BEGIN_NAMESPACE

void input(ComplexNumber &num) {
    double real, image;
    scanf("%lf %lf", &real, &image);
    num.setValue(real, image);
}

void output(const ComplexNumber &num) {
    printf("%.6lf ", num.real());
    if (num.image() <= 0.0) {
        printf("- ");
    } else {
        printf("+ ");
    }
    printf("%.6lf i", fabs(num.image()));
}

void outputLine(const ComplexNumber &num) {
    output(num);
    putchar('\n');
}

istream& operator >>(istream &in, ComplexNumber &num) {
    double real, image;
    in >> real >> image;
    num.setValue(real, image);
    return in;
}

ostream& operator <<(ostream &out, const ComplexNumber &num) {
    out << num.real();
    if (num.image() <= 0.0) {
        out << " - ";
    } else {
        out << " + ";
    }
    out << num.image() << " i";
    return out;
}

ZMAT_END_NAMESPACE
