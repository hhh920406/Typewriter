#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QImage>
#include <QPainter>
#include "gameobject.h"
#include "defination.h"
#include "achieve.h"
#include "math.h"

#define MaxItemNumber 144

class Environment
{
public:
    Environment();
    ~Environment();
    GameObject *gameObject[MaxItemNumber];
    void draw(QPainter *painter);
    bool hitTestType(qint32 x, qint32 y, qint32 width, qint32 height, qint32 type);
    bool hitTestMove(qint32 x, qint32 y, qint32 width, qint32 height, bool cat = false, bool trueCat = false);
    bool hitTestBullet(qint32 x, qint32 y ,qint32 width, qint32 height);
    void initialEnvironment();
    void initialBrick(GameObject *object);
    void initialSteel(GameObject *object);
    void initialRiver(GameObject *object);
    void initialCatStone(GameObject *object);
    void addItem(qint32 type, qint32 i, qint32 j);
    void deleteItem(qint32 id);
    void bindAchieve(Achieve *achieve);
    void initialStage(qint32 stage);

    bool catStoneExist();
    void trueCatPower();
private:
    QImage *river;
    QImage *steel;
    QImage *brick;
    QImage *catStone;
    Achieve *achieve;
    qint32 itemNumber;
};

#endif
