#include "Framework.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init("ZSTG v0.01", 960, 720, false);
    framework->messageLoop();
    return 0;
}
