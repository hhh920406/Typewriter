#include "Test.h"
#include "Test_ComplexNumber.h"
#include "Test_SolidMatrix.h"

int main()
{
    Test_ComplexNumber();
    Test_SolidMatrix();
    Test::test();
    return 0;
}
