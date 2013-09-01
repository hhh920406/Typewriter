#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "Sprite2D.h"
#include "SceneIncrease.h"
#include "Framework.h"
#include "Sprite2DController.h"
#include "Point2D.h"
#include "Vector2D.h"

const int MAX_SPRITE_NUM = 128;

SceneIncrease::SceneIncrease()
{
    this->_bulletNumMax = 0;
}

SceneIncrease::~SceneIncrease()
{
}

void SceneIncrease::load()
{
    Scene::load();
    Framework *framework = Framework::getInstance();
    framework->spriteController()->setTextureLocation(0, "bullet.png");
    this->_status = STATUS_WAITING;
    this->_bulletNum = 1;
    this->_player = new Sprite2D(20, 20);
    framework->spriteController()->initSprite(this->_player, 0, 448, 0, 512, 64, 1024, 1024);
    this->addSprite(this->_player);
    for (int i = 0; i < MAX_SPRITE_NUM; ++i)
    {
        Sprite2D *sprite = new Sprite2D(40, 40);
        framework->spriteController()->initSprite(sprite, 0, 320, 0, 384, 64, 1024, 1024);
        this->_sprites.push_back(sprite);
        this->addSprite(sprite);
    }
    restart();
    this->_status = STATUS_MOVING;
}

int SceneIncrease::act(int milliseconds)
{
    if (this->_status == STATUS_MOVING)
    {
        this->_seconds += milliseconds;
        if (this->_seconds >= 2000)
        {
            this->addBullet();
            this->_seconds -= 2000;
        }
        float width = Framework::getInstance()->windowWidth();
        float height = Framework::getInstance()->windowHeight();
        for (int i = 0; i < this->_bulletNum; ++i)
        {
            this->_sprites[i]->act(milliseconds);
            Point2D position = this->_sprites[i]->position();
            Vector2D velocity = this->_sprites[i]->velocity();
            if (position.x() < 0 || position.x() > width)
            {
                velocity.setX(-velocity.x());
            }
            if (position.y() < 0 || position.y() > height)
            {
                velocity.setY(-velocity.y());
            }
            this->_sprites[i]->setVelocity(velocity);
            if (this->dist(this->_sprites[i], this->_player) < 100.0)
            {
                this->_status = STATUS_WAITING;
            }
        }
        Point2D position = this->_player->position();
        float speed = 0.2f;
        if (Framework::getInstance()->keyState()->isPressed(KeyState::KEY_SHIFT))
        {
            speed = 0.1f;
        }
        if (Framework::getInstance()->keyState()->isPressed(KeyState::KEY_LEFT))
        {
            position.setX(position.x() - speed * milliseconds);
        }
        if (Framework::getInstance()->keyState()->isPressed(KeyState::KEY_RIGHT))
        {
            position.setX(position.x() + speed * milliseconds);
        }
        if (Framework::getInstance()->keyState()->isPressed(KeyState::KEY_UP))
        {
            position.setY(position.y() - speed * milliseconds);
        }
        if (Framework::getInstance()->keyState()->isPressed(KeyState::KEY_DOWN))
        {
            position.setY(position.y() + speed * milliseconds);
        }
        if (position.x() < 0.0f)
        {
            position.setX(0.0f);
        }
        else if (position.x() > width)
        {
            position.setX(width);
        }
        if (position.y() < 0.0f)
        {
            position.setY(0.0f);
        }
        else if (position.y() > height)
        {
            position.setY(height);
        }
        this->_player->translateTo(position.x(), position.y());
    }
    return this->sceneIndex();
}

int SceneIncrease::render()
{
    for (int i = 0; i < this->_bulletNum; ++i)
    {
        this->_sprites[i]->render();
    }
    this->_player->render();
    return this->sceneIndex();
}

void SceneIncrease::restart()
{
    this->_seconds = 0;
    float width = Framework::getInstance()->windowWidth();
    float height = Framework::getInstance()->windowHeight();
    this->_player->translateTo(width * 0.75f, height * 0.5f);
    this->_bulletNum = 1;
    this->_sprites[0]->translateTo(width * 0.25f, height * 0.5f);
    for (int i = 0; i < 10; ++i)
    {
        this->addBullet();
    }
}

void SceneIncrease::addBullet()
{
    if (this->_bulletNum < MAX_SPRITE_NUM)
    {
        double angle = rand() / 1000.0;
        double speed = (rand() % 50 + 10) / 400.0;
        float width = Framework::getInstance()->windowWidth();
        float height = Framework::getInstance()->windowHeight();
        this->_sprites[this->_bulletNum]->translateTo(width * 0.25f, height * 0.5f);
        this->_sprites[this->_bulletNum]->setVelocity(Vector2D(speed * cos(angle), speed * sin(angle)));
        if (++this->_bulletNum == MAX_SPRITE_NUM)
        {
            angle = rand() / 1000.0;
            speed = (rand() % 50 + 10) / 400.0;
            this->_sprites[0]->setVelocity(Vector2D(speed * cos(angle), speed * sin(angle)));
        }
        if (this->_bulletNum > this->_bulletNumMax)
        {
            this->_bulletNumMax = this->_bulletNum;
            printf("Hi-Score: %d\n", this->_bulletNumMax);
        }
    }
}

double SceneIncrease::dist(Sprite2D *a, Sprite2D *b)
{
    Point2D pa = a->position();
    Point2D pb = b->position();
    return (pa.x() - pb.x()) * (pa.x() - pb.x()) + (pa.y() - pb.y()) * (pa.y() - pb.y());
}
