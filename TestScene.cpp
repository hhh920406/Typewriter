#include <cstdlib>
#include "TestScene.h"
#include "Framework.h"
#include "Sprite2DController.h"
#include "TestSprite2D.h"

TestScene::TestScene() : Scene()
{
}

void TestScene::load()
{
    Scene::load();
    Framework *framework = Framework::getInstance();
    framework->spriteController()->setTextureLocation(0, "bullet.png");
    framework->spriteController()->setTextureLocation(1, "back.jpg");
    Sprite2D *back = new Sprite2D(960, 720);
    framework->spriteController()->initSprite(back, 1, 0, 0, 554, 341, 554, 341);
    back->translateTo(960 / 2, 720 / 2);
    this->addSprite(back);
    const double PI = acos(-1.0);
    int flag = 1;
    int angle = 0;
    for (int i = 0; i < 20000; ++i)
    {
        TestSprite2D *sprite = new TestSprite2D(40, 20);
        framework->spriteController()->initSprite(sprite, 0, 320, 0, 384, 64, 1024, 1024);
        sprite->setPosition(960 / 2, 720 / 2);
        float speed = 2.0f;
        if ((rand() % 1000) == 1)
        {
            flag = -flag;
        }
        angle += flag;
        sprite->setSpeed(speed * cos(angle / 1600.0 * PI * 2 + PI * (angle % 2)),
                         speed * sin(angle / 1600.0 * PI * 2 + PI * (angle % 2)));
        sprite->setBirth(i / 2);
        sprite->setBounding(960 / 2 - 300, 960 / 2 + 300, 720 / 2 - 300, 720 / 2 + 300);
        this->addSprite(sprite);
    }
    this->_player = new Sprite2D(30, 30);
    framework->spriteController()->initSprite(this->_player, 0,
                                              0, 0, 64, 64,
                                              1024, 1024);
    this->_x = 400;
    this->_y = 500;
    this->_sx = 0.0f;
    this->_sy = 0.0f;
    this->addSprite(this->_player);
}

int TestScene::act()
{
    Scene::act();
    Framework *framework = Framework::getInstance();
    KeyState *keyState = framework->keyState();
    float speed = 1.0f;
    float maxSpeed = 5.0f;
    if (keyState->isPressed(KeyState::KEY_SHIFT))
    {
        maxSpeed = 2.5f;
    }
    if (keyState->isPressed(KeyState::KEY_UP))
    {
        this->_sy -= speed;
    }
    else if (keyState->isPressed(KeyState::KEY_DOWN))
    {
        this->_sy += speed;
    }
    else
    {
        this->_sy *= 0.7f;
    }
    if (this->_sy < -maxSpeed)
    {
        this->_sy = -maxSpeed;
    }
    else if (this->_sy > maxSpeed)
    {
        this->_sy = maxSpeed;
    }
    if (keyState->isPressed(KeyState::KEY_LEFT))
    {
        this->_sx -= speed;
    }
    else if (keyState->isPressed(KeyState::KEY_RIGHT))
    {
        this->_sx += speed;
    }
    else
    {
        this->_sx *= 0.7f;
    }
    if (this->_sx < -maxSpeed)
    {
        this->_sx = -maxSpeed;
    }
    else if (this->_sx > maxSpeed)
    {
        this->_sx = maxSpeed;
    }
    this->_x += this->_sx;
    this->_y += this->_sy;
    this->_player->translateTo(this->_x, this->_y);
    return this->sceneIndex();
}
