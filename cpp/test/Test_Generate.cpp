#include "Test.h"
#include "Matrix.h"
#include "Matrix_math.h"
#include "Test_Generate.h"
using namespace zmat;

void Test_Generate_Eye()
{
    Matrix I = eye();
    TEST_EQUAL(I.rowNum(), 1);
    TEST_EQUAL(I.colNum(), 1);
    TEST_EQUAL(I(1, 1), Complex(1.0));
    I = eye(5);
    TEST_EQUAL(I.rowNum(), 5);
    TEST_EQUAL(I.colNum(), 5);
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = 1; j <= 5; ++j)
        {
            if (i == j)
            {
                TEST_EQUAL(I(i, j), Complex(1.0));
            }
            else
            {
                TEST_EQUAL(I(i, j), Complex(0.0));
            }
        }
    }
    I = eye(6, 10);
    TEST_EQUAL(I.rowNum(), 6);
    TEST_EQUAL(I.colNum(), 10);
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = 1; j <= 10; ++j)
        {
            if (i == j)
            {
                TEST_EQUAL(I(i, j), Complex(1.0));
            }
            else
            {
                TEST_EQUAL(I(i, j), Complex(0.0));
            }
        }
    }
    I = eye(10, 2);
    TEST_EQUAL(I.rowNum(), 10);
    TEST_EQUAL(I.colNum(), 2);
    for (int i = 1; i <= 10; ++i)
    {
        for (int j = 1; j <= 2; ++j)
        {
            if (i == j)
            {
                TEST_EQUAL(I(i, j), Complex(1.0));
            }
            else
            {
                TEST_EQUAL(I(i, j), Complex(0.0));
            }
        }
    }
}

void Test_Generate()
{
    Test::add("Generate", "Eye", Test_Generate_Eye);
}
