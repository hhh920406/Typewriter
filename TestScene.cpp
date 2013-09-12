#include <cstdlib>
#include "TestScene.h"
#include "Framework.h"
#include "Sprite2DController.h"
#include "Widget.h"
#include "WidgetController.h"
#include "TestSprite2D.h"

TestScene::TestScene() : Scene()
{
}

void TestScene::load()
{
    Scene::load();
    Framework *framework = Framework::getInstance();
    framework->spriteController()->setTextureLocation(0, "bullet.png");
    const double PI = acos(-1.0);
    int flag = 1;
    int angle = 0;
    for (int i = 0; i < 20000; ++i)
    {
        TestSprite2D *sprite;
        switch (i % 3)
        {
        case 0:
            sprite = new TestSprite2D(30, 30);
            framework->spriteController()->initSprite(sprite, 0, 384, 192, 448, 256, 1024, 1024);
            sprite->setVelocity(Vector2D(0.09 * cos(PI * 2 * (i / 6) / 60.0 + (i % 6) * PI),
                                         0.09 * sin(PI * 2 * (i / 6) / 60.0 + (i % 6) * PI)));
            break;
        case 1:
            sprite = new TestSprite2D(30, 30);
            framework->spriteController()->initSprite(sprite, 0, 320, 192, 384, 256, 1024, 1024);
            sprite->setVelocity(Vector2D(0.08 * cos(PI * 2 * (i / 6) / 70.0 + (i % 6) * PI + PI / 3 * 2),
                                         -0.08 * sin(PI * 2 * (i / 6) / 70.0 + (i % 6) * PI + PI / 3 * 2)));
            break;
        case 2:
            sprite = new TestSprite2D(30, 30);
            framework->spriteController()->initSprite(sprite, 0, 0, 192, 64, 256, 1024, 1024);
            sprite->setVelocity(Vector2D(0.07 * cos(PI * 2 * (i / 6) / 80.0 + (i % 6) * PI - PI / 3 * 2),
                                         0.07 * sin(PI * 2 * (i / 6) / 80.0 + (i % 6) * PI - PI / 3 * 2)));
            break;
        }
        sprite->setBirth(i / 3);
        sprite->translateTo(50 + 500 / 2, 50 + 500 / 2);
        sprite->setBounding(50, 550, 50, 550);
        this->addSprite(sprite);
    }
    framework->widgetController()->setTextureLocation(1, "back.png");
    Widget *widget;
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              0, 0, 50, 600,
                                              0, 0, 50, 600,
                                              800, 600);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              50, 0, 550, 50,
                                              50, 0, 600, 50,
                                              800, 600);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              50, 550, 550, 50,
                                              50, 550, 600, 600,
                                              800, 600);
    this->addWidget(widget);
    widget = new Widget();
    framework->widgetController()->initWidget(widget, 1,
                                              550, 0, 250, 600,
                                              550, 0, 800, 600,
                                              800, 600);
    this->addWidget(widget);
}
