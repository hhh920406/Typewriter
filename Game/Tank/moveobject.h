#ifndef MOVEOBJECT_H
#define MOVEOBJECT_H

#include "gameobject.h"
#include "defination.h"
#include "environment.h"

class MoveObject : public GameObject
{
public:
    MoveObject();
    bool stay;
    qint32 speed;
    qint32 moveDirection;
    bool move(Environment *environment);
    bool outJudge();
};

#endif
