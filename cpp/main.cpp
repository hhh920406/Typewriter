#include "Test.h"
#include "Test_Complex.h"
#include "Test_Matrix.h"
#include "Test_Decompose.h"

int main() {
    Test_Complex();
    Test_Matrix();
    Test_Decompose();
    Test::test();
    return 0;
}
