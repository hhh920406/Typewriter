#ifndef TESTSCENE_H
#define TESTSCENE_H

#include "Scene.h"

class TestScene : public Scene
{
public:
    TestScene();

    virtual void load();

    virtual int act();

private:
    Sprite2D *_player;
    float _x;
    float _y;
    float _sx;
    float _sy;
};

#endif // TESTSCENE_H
