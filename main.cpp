#include "Framework.h"
#include "TestSprite2D.h"

int main()
{
    Framework *framework = Framework::getInstance();
    framework->init("Framework", 800, 600, true);
    framework->spriteController()->setTextureLocation(0, "bullet.png");
    framework->spriteController()->setTextureLocation(1, "back.jpg");
    Sprite2D *back = new Sprite2D(800, 600);
    framework->spriteController()->initSprite(back, 1, 0, 0, 554, 341, 554, 341);
    back->translateTo(800 / 2, 600 / 2);
    const double PI = acos(-1.0);
    for (int i = 0; i < 20000; ++i)
    {
        TestSprite2D *sprite = new TestSprite2D(40, 20);
        framework->spriteController()->initSprite(sprite, 0, 0, 0, 64, 64, 1024, 1024);
        sprite->setPosition(800 / 2, 600 / 2);
        float speed = 2.0f;
        sprite->setSpeed(speed * cos(i / 800.0 * PI * 2 + PI / 4 * (i % 8)),
                         speed * sin(i / 800.0 * PI * 2 + PI / 4 * (i % 8)));
        sprite->setBirth(i);
        sprite->setBounding(0, 800, 0, 600);
    }
    framework->messageLoop();
    return 0;
}
