#include "Test.h"
#include "Complex.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace zmat;

void Test_Complex_Equal() {
    Complex a(5, 3);
    Complex b;
    TEST_EQUAL(b, Complex(0, 0));
    TEST_UNEQUAL(b, a);
    b.setValue(5, 3);
    TEST_EQUAL(a, b);
}

void Test_Complex_Norm() {
    Complex a(-3, 4);
    Complex b(3, 4);
    TEST_AEQUAL(norm(a), 5.0);
    TEST_AEQUAL(norm(b), 5.0);
}

void Test_Complex_Angle() {
    Complex a(-3, 4);
    Complex b(3, 4);
    TEST_AEQUAL(angle(a), atan2(4, -3));
    TEST_AEQUAL(angle(b), atan2(4, 3));
}

void Test_Complex_Conjugate() {
    Complex a(3, 4);
    Complex b(3, -4);
    TEST_EQUAL(conjugate(a), b);
    TEST_EQUAL(conjugate(b), a);
}

void Test_Complex_Add() {
    Complex a(-5, 8);
    Complex b(4, 5);
    Complex c(-1, 13);
    TEST_EQUAL(a + b, c);
}

void Test_Complex_Subtract() {
    Complex a(-5, 8);
    Complex b(4, 5);
    Complex c(-9, 3);
    TEST_EQUAL(a - b, c);
}

void Test_Complex_Multiply() {
    Complex a(-5, 8);
    Complex b(4, 5);
    Complex c(-60, 7);
    TEST_EQUAL(a * b, c);
}

void Test_Complex_Divide() {
    Complex a(-5, 8);
    Complex b(3, 4);
    Complex c(17 / 25.0, 44 / 25.0);
    TEST_EQUAL(a / b, c);
}

void Test_Complex() {
    Test::add("Complex", "Equal", Test_Complex_Equal);
    Test::add("Complex", "Norm", Test_Complex_Norm);
    Test::add("Complex", "Angle", Test_Complex_Angle);
    Test::add("Complex", "Conjugate", Test_Complex_Conjugate);
    Test::add("Complex", "Add", Test_Complex_Add);
    Test::add("Complex", "Subtract", Test_Complex_Subtract);
    Test::add("Complex", "Multiply", Test_Complex_Multiply);
    Test::add("Complex", "Divide", Test_Complex_Divide);
}
