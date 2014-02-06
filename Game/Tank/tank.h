#ifndef TANK_H
#define TANK_H

#include <math.h>
#include "moveobject.h"
#include "environment.h"

class Tank : public MoveObject
{
public:
    Tank();
    ~Tank();
    qint32 currentBulletNumber;
    qint32 maximumBulletNumber;
    qint32 currentMineNumber;
    qint32 maximumMineNumber;
    qint32 bulletStatus;
    qint32 mineStatus;
    MoveObject *bullet[5];
    MoveObject *mine[5];
    bool move(Environment *environment, Tank *tank);
    bool move(Environment *environment, Tank *tank[], qint32 tankNumber);
    void fire();
    void setMine();
    void turnLeft();
    void turnRight();
    void turnBack();
    bool hitTestIn(MoveObject *object, qint32 x, qint32 y, qint32 width, qint32 height);
    bool inArea(qint32 tx, qint32 ty, qint32 x, qint32 y, qint32 width, qint32 height);
    void autoMove(Environment *environment, qint32 level);
    void autoMoveLevel0(Environment *environment);
    void autoMoveLevel1(Environment *environment);
    void draw(QPainter *painter, QImage *tank[4], QImage *bullet[4], QImage *mine, Environment *environment);
    void draw(QPainter *painter, QImage *tank, QImage *bullet[4], QImage *mine, Environment *environment);
    qint32 hitTestBullet(qint32 x, qint32 y, qint32 width, qint32 height);

    qint32 energy;
    qint32 maxEnergy;
    qint32 decreaseCatEnergy;
    qint32 decreaseTrueCatEnergy;
    bool catStatus;
    bool trueCatStatus;
    void cat();
    void catDecrease();
    void setEnergy(qint32 value);
};

#endif
