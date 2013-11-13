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
    TEST_EQUAL(b, ComplexNumber(0, 0));
    TEST_UNEQUAL(b, a);
    b.setValue(5, 3);
    TEST_EQUAL(a, b);
}

void Test_ComplexNumber_Norm() {
    ComplexNumber a(-3, 4);
    ComplexNumber b(3, 4);
    TEST_AEQUAL(norm(a), 5.0);
    TEST_AEQUAL(norm(b), 5.0);
}

void Test_ComplexNumber_Angle() {
    ComplexNumber a(-3, 4);
    ComplexNumber b(3, 4);
    TEST_AEQUAL(angle(a), atan2(4, -3));
    TEST_AEQUAL(angle(b), atan2(4, 3));
}

void Test_ComplexNumber_Conjugate() {
    ComplexNumber a(3, 4);
    ComplexNumber b(3, -4);
    TEST_EQUAL(conjugate(a), b);
    TEST_EQUAL(conjugate(b), a);
}

void Test_ComplexNumber_Add() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(4, 5);
    ComplexNumber c(-1, 13);
    TEST_EQUAL(a + b, c);
}

void Test_ComplexNumber_Subtract() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(4, 5);
    ComplexNumber c(-9, 3);
    TEST_EQUAL(a - b, c);
}

void Test_ComplexNumber_Multiply() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(4, 5);
    ComplexNumber c(-60, 7);
    TEST_EQUAL(a * b, c);
}

void Test_ComplexNumber_Divide() {
    ComplexNumber a(-5, 8);
    ComplexNumber b(3, 4);
    ComplexNumber c(17 / 25.0, 44 / 25.0);
    TEST_EQUAL(a / b, c);
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
