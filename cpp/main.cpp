#include "Test.h"
#include "Test_ComplexNumber.h"
#include "Test_SolidMatrix.h"
#include "Test_Decompose.h"

int main()
{
    Test_ComplexNumber();
    Test_SolidMatrix();
    Test_Decompose();
    Test::test();
    return 0;
}
