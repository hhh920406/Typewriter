#include "Framework.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init("Framework", 960, 720, false);
    framework->messageLoop();
    return 0;
}