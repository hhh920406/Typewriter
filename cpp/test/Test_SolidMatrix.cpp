#include "Test.h"
#include "SolidMatrix.h"
#include "SolidMatrix_io.h"
#include "SolidMatrix_arithmetic.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace zmat;

void Test_SolidMatrix_Equal() {
    SolidMatrix a(3, 3);
    SolidMatrix b(3, 3);
    SolidMatrix c(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a.setData(i, j, i + j);
            b.setData(i, j, j + i);
            c.setData(i, j, i - j);
        }
    }
    TEST_EQUAL(a, b);
    TEST_EQUAL(b, a);
    TEST_UNEQUAL(a, c);
    TEST_UNEQUAL(c, a);
    TEST_UNEQUAL(b, c);
    TEST_UNEQUAL(c, b);
}

void Test_SolidMatrix_Add() {
    SolidMatrix a(3, 3);
    SolidMatrix b(3, 3);
    SolidMatrix c(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a.setData(i, j, i + j);
            b.setData(i, j, i - j);
            c.setData(i, j, i * 2);
        }
    }
    TEST_EQUAL(a + b, c);
    TEST_EQUAL(b + a, c);
}

void Test_SolidMatrix_Subtract() {
    SolidMatrix a(3, 3);
    SolidMatrix b(3, 3);
    SolidMatrix c(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a.setData(i, j, i + j);
            b.setData(i, j, i - j);
            c.setData(i, j, j * 2);
        }
    }
    TEST_EQUAL(a - b, c);
    TEST_UNEQUAL(b - a, c);
}

void Test_SolidMatrix_Multiply() {
    SolidMatrix a(3, 3);
    SolidMatrix b(3, 3);
    SolidMatrix c(3, 3);
    SolidMatrix d(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a.setData(i, j, i + j);
            b.setData(i, j, i - j);
        }
    }
    c.setData(1, 1, 11);
    c.setData(1, 2, 2);
    c.setData(1, 3, -7);
    c.setData(2, 1, 14);
    c.setData(2, 2, 2);
    c.setData(2, 3, -10);
    c.setData(3, 1, 17);
    c.setData(3, 2, 2);
    c.setData(3, 3, -13);
    TEST_EQUAL(a * b, c);
    d.setData(1, 1, -11);
    d.setData(1, 2, -14);
    d.setData(1, 3, -17);
    d.setData(2, 1, -2);
    d.setData(2, 2, -2);
    d.setData(2, 3, -2);
    d.setData(3, 1, 7);
    d.setData(3, 2, 10);
    d.setData(3, 3, 13);
    TEST_EQUAL(b * a, d);
}

void Test_SolidMatrix() {
    Test::add("SolidMatrix", "Equal", Test_SolidMatrix_Equal);
    Test::add("SolidMatrix", "Add", Test_SolidMatrix_Add);
    Test::add("SolidMatrix", "Subtract", Test_SolidMatrix_Subtract);
    Test::add("SolidMatrix", "Multiply", Test_SolidMatrix_Multiply);
}
