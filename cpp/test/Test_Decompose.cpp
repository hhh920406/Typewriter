#include "Test.h"
#include "Matrix.h"
#include "Matrix_math.h"
using namespace zmat;

void Test_Decompose_Doolittle() {
    Matrix a(4, 4);
    a(1, 1) = 2; a(1, 2) = 1; a(1, 3) = 1; a(1, 4) = 0;
    a(2, 1) = 4; a(2, 2) = 3; a(2, 3) = 3; a(2, 4) = 1;
    a(3, 1) = 8; a(3, 2) = 7; a(3, 3) = 9; a(3, 4) = 5;
    a(4, 1) = 6; a(4, 2) = 7; a(4, 3) = 9; a(4, 4) = 8;
    Matrix b(4, 4);
    b(1, 1) = 1; b(1, 2) = 0; b(1, 3) = 0; b(1, 4) = 0;
    b(2, 1) = 2; b(2, 2) = 1; b(2, 3) = 0; b(2, 4) = 0;
    b(3, 1) = 4; b(3, 2) = 3; b(3, 3) = 1; b(3, 4) = 0;
    b(4, 1) = 3; b(4, 2) = 4; b(4, 3) = 1; b(4, 4) = 1;
    Matrix c(4, 4);
    c(1, 1) = 2; c(1, 2) = 1; c(1, 3) = 1; c(1, 4) = 0;
    c(2, 1) = 0; c(2, 2) = 1; c(2, 3) = 1; c(2, 4) = 1;
    c(3, 1) = 0; c(3, 2) = 0; c(3, 3) = 2; c(3, 4) = 2;
    c(4, 1) = 0; c(4, 2) = 0; c(4, 3) = 0; c(4, 4) = 2;
    Doolittle_Mat doo = doolittle(a);
    TEST_EQUAL(doo.L, b);
    TEST_EQUAL(doo.U, c);
    TEST_EQUAL(doo.L * doo.U, a);
}

void Test_Decompose() {
    Test::add("Decompose", "Doolittle", Test_Decompose_Doolittle);
}
