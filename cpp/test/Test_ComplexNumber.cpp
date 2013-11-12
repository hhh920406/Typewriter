#include "Test.h"
#include "ComplexNumber.h"
#include "ComplexNumber_io.h"
#include "ComplexNumber_math.h"
#include "ComplexNumber_arithmetic.h"
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

void Test_ComplexNumber() {
    Test::add("ComplexNumber", "Equal", Test_ComplexNumber_Equal);
}
