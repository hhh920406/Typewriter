#include "Framework.h"
#include "TestSprite2D.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init("Framework", 960, 720, false);
    const double PI = acos(-1.0);
    for (int i = 0; i < 255; ++i)
    {
        TestSprite2D *sprite = new TestSprite2D(50, 50);
        framework->spriteController()->setTextureLocation(0, "bullet.png");
        framework->spriteController()->initSprite(sprite, 0, 128, 256, 256, 384, 1024, 1024);
        sprite->setPosition(960 / 2, 720 / 2);
        sprite->setSpeed(((i % 15) + 2) * 1, ((i % 17) + 2) * 1);
        sprite->setBounding(0, 960, 0, 720);
    }
    framework->messageLoop();
    return 0;
}
