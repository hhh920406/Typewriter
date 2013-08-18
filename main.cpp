#include "Framework.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init();
    framework->messageLoop();
    return 0;
}
