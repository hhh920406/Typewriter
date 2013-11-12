#include <cmath>
#include <cstdio>
#include "ComplexNumber.h"
#include "ComplexNumber_io.h"

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

ZMAT_END_NAMESPACE
