#ifndef SCENEINCREASE_H
#define SCENEINCREASE_H

#include <vector>
#include "Scene.h"
#include "KeyState.h"

class SceneIncrease : public Scene
{
public:
    SceneIncrease();
    virtual ~SceneIncrease();

    virtual void load();

    virtual int act(int milliseconds);
    virtual int render();

private:
    enum Status
    {
        STATUS_WAITING,
        STATUS_MOVING
    } _status;
    int _bulletNum;
    int _bulletNumMax;
    std::vector<Sprite2D*> _sprites;
    Sprite2D* _player;
    int _seconds;

    void restart();
    void addBullet();
    double dist(Sprite2D *a, Sprite2D *b);
};

#endif // SCENEINCREASE_H
