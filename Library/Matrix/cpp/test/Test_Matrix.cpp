#include "Test.h"
#include "Matrix.h"
#include "Matrix_math.h"
using namespace zmat;

void Test_Matrix_Equal()
{
    Matrix<Complex> a(3, 3);
    Matrix<Complex> b(3, 3);
    Matrix<Complex> c(3, 3);
    for (int i = 1; i <= 3; ++i)
    {
        for (int j = 1; j <= 3; ++j)
        {
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

void Test_Matrix_Add()
{
    Matrix<Complex> a(3, 3);
    Matrix<Complex> b(3, 3);
    Matrix<Complex> c(3, 3);
    for (int i = 1; i <= 3; ++i)
    {
        for (int j = 1; j <= 3; ++j)
            {
            a(i, j) = i + j;
            b(i, j) = i - j;
            c(i, j) = i * 2;
        }
    }
    TEST_EQUAL(a + b, c);
    TEST_EQUAL(b + a, c);
}

void Test_Matrix_Subtract()
{
    Matrix<Complex> a(3, 3);
    Matrix<Complex> b(3, 3);
    Matrix<Complex> c(3, 3);
    for (int i = 1; i <= 3; ++i)
    {
        for (int j = 1; j <= 3; ++j)
            {
            a(i, j) = i + j;
            b(i, j) = i - j;
            c(i, j) = j * 2;
        }
    }
    TEST_EQUAL(a - b, c);
    TEST_UNEQUAL(b - a, c);
}

void Test_Matrix_Multiply()
{
    Matrix<Complex> a(3, 3);
    Matrix<Complex> b(3, 3);
    Matrix<Complex> c(3, 3);
    Matrix<Complex> d(3, 3);
    for (int i = 1; i <= 3; ++i)
    {
        for (int j = 1; j <= 3; ++j)
        {
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

void Test_Matrix_Inverse()
{
    Matrix<Complex> a(4, 4);
    a(1, 1) = 2; a(1, 2) = 1; a(1, 3) = 1; a(1, 4) = 0;
    a(2, 1) = 4; a(2, 2) = 3; a(2, 3) = 3; a(2, 4) = 1;
    a(3, 1) = 8; a(3, 2) = 7; a(3, 3) = 9; a(3, 4) = 5;
    a(4, 1) = 6; a(4, 2) = 7; a(4, 3) = 9; a(4, 4) = 8;
    TEST_EQUAL(a * inv(a), eye<Complex>(4));
    TEST_EQUAL(inv(a) * a, eye<Complex>(4));
}

void Test_Matrix_Transpose()
{
    Matrix<Complex> a(4, 4);
    a(1, 1) = 2; a(1, 2) = 1; a(1, 3) = 1; a(1, 4) = 0;
    a(2, 1) = 4; a(2, 2) = 3; a(2, 3) = 3; a(2, 4) = 1;
    a(3, 1) = 8; a(3, 2) = 7; a(3, 3) = 9; a(3, 4) = 5;
    a(4, 1) = 6; a(4, 2) = 7; a(4, 3) = 9; a(4, 4) = 8;
    Matrix<Complex> b = transpose(a);
    for (int i = 1; i <= a.rowNum(); ++i)
    {
        for (int j = 1; j <= a.colNum(); ++j)
        {
            TEST_EQUAL(a(i, j), b(j, i));
        }
    }
}

void Test_Matrix()
{
    Test::add("Matrix", "Equal", Test_Matrix_Equal);
    Test::add("Matrix", "Add", Test_Matrix_Add);
    Test::add("Matrix", "Subtract", Test_Matrix_Subtract);
    Test::add("Matrix", "Multiply", Test_Matrix_Multiply);
    Test::add("Matrix", "Inverse", Test_Matrix_Inverse);
    Test::add("Matrix", "Transpose", Test_Matrix_Transpose);
}
