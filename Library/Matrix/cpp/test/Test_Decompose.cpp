#include "Test.h"
#include "Matrix.h"
#include "Matrix_math.h"
using namespace zmat;

void Test_Decompose_Doolittle()
{
    Matrix<Complex> a(4, 4);
    a(1, 1) = 2; a(1, 2) = 1; a(1, 3) = 1; a(1, 4) = 0;
    a(2, 1) = 4; a(2, 2) = 3; a(2, 3) = 3; a(2, 4) = 1;
    a(3, 1) = 8; a(3, 2) = 7; a(3, 3) = 9; a(3, 4) = 5;
    a(4, 1) = 6; a(4, 2) = 7; a(4, 3) = 9; a(4, 4) = 8;
    Matrix<Complex> b(4, 4);
    b(1, 1) = 1; b(1, 2) = 0; b(1, 3) = 0; b(1, 4) = 0;
    b(2, 1) = 2; b(2, 2) = 1; b(2, 3) = 0; b(2, 4) = 0;
    b(3, 1) = 4; b(3, 2) = 3; b(3, 3) = 1; b(3, 4) = 0;
    b(4, 1) = 3; b(4, 2) = 4; b(4, 3) = 1; b(4, 4) = 1;
    Matrix<Complex> c(4, 4);
    c(1, 1) = 2; c(1, 2) = 1; c(1, 3) = 1; c(1, 4) = 0;
    c(2, 1) = 0; c(2, 2) = 1; c(2, 3) = 1; c(2, 4) = 1;
    c(3, 1) = 0; c(3, 2) = 0; c(3, 3) = 2; c(3, 4) = 2;
    c(4, 1) = 0; c(4, 2) = 0; c(4, 3) = 0; c(4, 4) = 2;
    Doolittle_Mat<Complex> doo = doolittle(a);
    TEST_EQUAL(doo.L, b);
    TEST_EQUAL(doo.U, c);
    TEST_EQUAL(doo.L * doo.U, a);
}

void Test_Decompose_LDU()
{
    Matrix<Complex> a(4, 4);
    a(1, 1) = 2; a(1, 2) = 1; a(1, 3) = 1; a(1, 4) = 0;
    a(2, 1) = 4; a(2, 2) = 3; a(2, 3) = 3; a(2, 4) = 1;
    a(3, 1) = 8; a(3, 2) = 7; a(3, 3) = 9; a(3, 4) = 5;
    a(4, 1) = 6; a(4, 2) = 7; a(4, 3) = 9; a(4, 4) = 8;
    Matrix<Complex> b(4, 4);
    b(1, 1) = 1; b(1, 2) = 0; b(1, 3) = 0; b(1, 4) = 0;
    b(2, 1) = 2; b(2, 2) = 1; b(2, 3) = 0; b(2, 4) = 0;
    b(3, 1) = 4; b(3, 2) = 3; b(3, 3) = 1; b(3, 4) = 0;
    b(4, 1) = 3; b(4, 2) = 4; b(4, 3) = 1; b(4, 4) = 1;
    Matrix<Complex> c(4, 4);
    c(1, 1) = 2; c(1, 2) = 0; c(1, 3) = 0; c(1, 4) = 0;
    c(2, 1) = 0; c(2, 2) = 1; c(2, 3) = 0; c(2, 4) = 0;
    c(3, 1) = 0; c(3, 2) = 0; c(3, 3) = 2; c(3, 4) = 0;
    c(4, 1) = 0; c(4, 2) = 0; c(4, 3) = 0; c(4, 4) = 2;
    Matrix<Complex> d(4, 4);
    d(1, 1) = 1; d(1, 2) = 0.5; d(1, 3) = 0.5; d(1, 4) = 0;
    d(2, 1) = 0; d(2, 2) = 1; d(2, 3) = 1; d(2, 4) = 1;
    d(3, 1) = 0; d(3, 2) = 0; d(3, 3) = 1; d(3, 4) = 1;
    d(4, 1) = 0; d(4, 2) = 0; d(4, 3) = 0; d(4, 4) = 1;
    LDU_Mat<Complex> ldu_mat = ldu(a);
    TEST_EQUAL(ldu_mat.L, b);
    TEST_EQUAL(ldu_mat.D, c);
    TEST_EQUAL(ldu_mat.U, d);
    TEST_EQUAL(ldu_mat.L * ldu_mat.D * ldu_mat.U, a);
}

void Test_Decompose_Crout()
{
    Matrix<Complex> a(4, 4);
    a(1, 1) = 2; a(1, 2) = 1; a(1, 3) = 1; a(1, 4) = 0;
    a(2, 1) = 4; a(2, 2) = 3; a(2, 3) = 3; a(2, 4) = 1;
    a(3, 1) = 8; a(3, 2) = 7; a(3, 3) = 9; a(3, 4) = 5;
    a(4, 1) = 6; a(4, 2) = 7; a(4, 3) = 9; a(4, 4) = 8;
    Matrix<Complex> b(4, 4);
    b(1, 1) = 2; b(1, 2) = 0; b(1, 3) = 0; b(1, 4) = 0;
    b(2, 1) = 4; b(2, 2) = 1; b(2, 3) = 0; b(2, 4) = 0;
    b(3, 1) = 8; b(3, 2) = 3; b(3, 3) = 2; b(3, 4) = 0;
    b(4, 1) = 6; b(4, 2) = 4; b(4, 3) = 2; b(4, 4) = 2;
    Matrix<Complex> d(4, 4);
    d(1, 1) = 1; d(1, 2) = 0.5; d(1, 3) = 0.5; d(1, 4) = 0;
    d(2, 1) = 0; d(2, 2) = 1; d(2, 3) = 1; d(2, 4) = 1;
    d(3, 1) = 0; d(3, 2) = 0; d(3, 3) = 1; d(3, 4) = 1;
    d(4, 1) = 0; d(4, 2) = 0; d(4, 3) = 0; d(4, 4) = 1;
    Crout_Mat<Complex> cro = crout(a);
    TEST_EQUAL(cro.L, b);
    TEST_EQUAL(cro.U, d);
    TEST_EQUAL(cro.L * cro.U, a);
}

void Test_Decompose()
{
    Test::add("Decompose", "Doolittle", Test_Decompose_Doolittle);
    Test::add("Decompose", "LDU", Test_Decompose_LDU);
    Test::add("Decompose", "Crout", Test_Decompose_Crout);
}
