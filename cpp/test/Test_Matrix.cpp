#include "Test.h"
#include "Matrix.h"
#include <cmath>
#include <iostream>
using namespace std;
using namespace zmat;

void Test_Matrix_Equal() {
    Matrix a(3, 3);
    Matrix b(3, 3);
    Matrix c(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a(i, j) = i + j;
            b(i, j) = j + i;
            c(i, j) = i - j;
        }
    }
    TEST_EQUAL(a, b);
    TEST_EQUAL(b, a);
    TEST_UNEQUAL(a, c);
    TEST_UNEQUAL(c, a);
    TEST_UNEQUAL(b, c);
    TEST_UNEQUAL(c, b);
}

void Test_Matrix_Add() {
    Matrix a(3, 3);
    Matrix b(3, 3);
    Matrix c(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a(i, j) = i + j;
            b(i, j) = i - j;
            c(i, j) = i * 2;
        }
    }
    TEST_EQUAL(a + b, c);
    TEST_EQUAL(b + a, c);
}

void Test_Matrix_Subtract() {
    Matrix a(3, 3);
    Matrix b(3, 3);
    Matrix c(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a(i, j) = i + j;
            b(i, j) = i - j;
            c(i, j) = j * 2;
        }
    }
    TEST_EQUAL(a - b, c);
    TEST_UNEQUAL(b - a, c);
}

void Test_Matrix_Multiply() {
    Matrix a(3, 3);
    Matrix b(3, 3);
    Matrix c(3, 3);
    Matrix d(3, 3);
    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            a(i, j) = i + j;
            b(i, j) = i - j;
        }
    }
    c(1, 1) = 11;   c(1, 2) = 2;    c(1, 3) = -7;
    c(2, 1) = 14;   c(2, 2) = 2;    c(2, 3) = -10;
    c(3, 1) = 17;   c(3, 2) = 2;    c(3, 3) = -13;
    TEST_EQUAL(a * b, c);
    d(1, 1) = -11;  d(1, 2) = -14;  d(1, 3) = -17;
    d(2, 1) = -2;   d(2, 2) = -2;   d(2, 3) = -2;
    d(3, 1) = 7;    d(3, 2) = 10;   d(3, 3) = 13;
    TEST_EQUAL(b * a, d);
}

void Test_Matrix() {
    Test::add("Matrix", "Equal", Test_Matrix_Equal);
    Test::add("Matrix", "Add", Test_Matrix_Add);
    Test::add("Matrix", "Subtract", Test_Matrix_Subtract);
    Test::add("Matrix", "Multiply", Test_Matrix_Multiply);
}
