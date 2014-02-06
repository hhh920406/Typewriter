#include "Test.h"
#include "Test_Complex.h"
#include "Test_Matrix.h"
#include "Test_Decompose.h"
#include "Test_Generate.h"

int main()
{
    Test_Complex();
    Test_Matrix();
    Test_Decompose();
    Test_Generate();
    Test::test();
    return 0;
}
