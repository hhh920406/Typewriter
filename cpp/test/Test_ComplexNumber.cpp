#include "Test.h"
#include "ComplexNumber.h"
#include "ComplexNumber_io.h"
#include "ComplexNumber_math.h"
#include "ComplexNumber_arithmetic.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace zmat;

void Test_ComplexNumber_Equal() {
    ComplexNumber a(5, 3);
    ComplexNumber b;
    if (Test::positive(b == ComplexNumber(0, 0))) {
        outputLine(b);
        outputLine(ComplexNumber(0, 0));
    }
    if (Test::negative(a == b)) {
        outputLine(a);
        outputLine(b);
    }
    b.setValue(5, 3);
    if (Test::positive(a == b)) {
        outputLine(a);
        outputLine(b);
    }
}

void Test_ComplexNumber_Norm() {
    ComplexNumber a(-3, 4);
    ComplexNumber b(3, 4);
    if (Test::positive(fabs(norm(a) - 5.0) < 1e-6)) {
        outputLine(a);
        cout << norm(a) << endl;
    }
    if (Test::positive(fabs(norm(b) - 5.0) < 1e-6)) {
        outputLine(a);
        cout << norm(a) << endl;
    }
}

void Test_ComplexNumber_Angle() {
    ComplexNumber a(-3, 4);
    ComplexNumber b(3, 4);
    if (Test::positive(fabs(angle(a) - atan2(4, -3)) < 1e-6)) {
        outputLine(a);
        cout << angle(a) << " " << atan2(4, -3) << endl;
    }
    if (Test::positive(fabs(angle(b) - atan2(4, 3)) < 1e-6)) {
        outputLine(a);
        cout << angle(b) << " " << atan2(4, 3) << endl;
    }
}

void Test_ComplexNumber_Conjugate() {
    ComplexNumber a(3, 4);
    ComplexNumber b(3, -4);
    if (Test::positive(conjugate(a) == b)) {
        outputLine(a);
        outputLine(b);
    }
    if (Test::positive(a == conjugate(b))) {
        outputLine(a);
        outputLine(b);
    }
}

void Test_ComplexNumber_Add() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(4, 5);
    ComplexNumber c(-1, 13);
    if (Test::positive(a + b == c)) {
        outputLine(a);
        outputLine(b);
        outputLine(a + b);
        outputLine(c);
    }
}

void Test_ComplexNumber_Subtract() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(4, 5);
    ComplexNumber c(-9, 3);
    if (Test::positive(a - b == c)) {
        outputLine(a);
        outputLine(b);
        outputLine(a - b);
        outputLine(c);
    }
}

void Test_ComplexNumber_Multiply() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(4, 5);
    ComplexNumber c(-60, 7);
    if (Test::positive(a * b == c)) {
        outputLine(a);
        outputLine(b);
        outputLine(a * b);
        outputLine(c);
    }
}

void Test_ComplexNumber_Divide() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(3, 4);
    ComplexNumber c(17 / 25.0, 44 / 25.0);
    if (Test::positive(a / b == c)) {
        outputLine(a);
        outputLine(b);
        outputLine(a * conjugate(b));
        outputLine(a / b);
        outputLine(c);
    }
}

void Test_ComplexNumber() {
    Test::add("ComplexNumber", "Equal", Test_ComplexNumber_Equal);
    Test::add("ComplexNumber", "Norm", Test_ComplexNumber_Norm);
    Test::add("ComplexNumber", "Angle", Test_ComplexNumber_Angle);
    Test::add("ComplexNumber", "Conjugate", Test_ComplexNumber_Conjugate);
    Test::add("ComplexNumber", "Add", Test_ComplexNumber_Add);
    Test::add("ComplexNumber", "Subtract", Test_ComplexNumber_Subtract);
    Test::add("ComplexNumber", "Multiply", Test_ComplexNumber_Multiply);
    Test::add("ComplexNumber", "Divide", Test_ComplexNumber_Divide);
}
