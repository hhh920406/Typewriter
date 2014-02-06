#ifndef GAME_H
#define GAME_H

#include <QImage>
#include <QPainter>
#include <QKeyEvent>
#include <math.h>
#include "moveobject.h"
#include "tank.h"
#include "defination.h"
#include "environment.h"
#include "integer.h"
#include "fraction.h"
#include "achieve.h"
#include "config.h"

#define MaxTankNumber 5

class Game
{
public:
    Game();
    ~Game();
    qint32 draw(QPainter *painter, qint32 &time);
    void keyDown(QKeyEvent *e);
    qint32 keyRelease(QKeyEvent *e);
    void bindAchieve(Achieve *achieve);
    void bindConfig(Config *config);
    void initialStage(qint32 stage);
    qint32 currentStage;
private:
    QImage *background;
    QImage *self[4];
    QImage *enemy1[4];
    QImage *bullet[4];
    QImage *mine;
    QImage *catTeacherW;
    QImage *catTeacherB;
    Tank *selfTank;
    Tank *enemyTank[MaxTankNumber];
    Environment *environment;
    Achieve *achieve;
    Config *config;
    Integer *highScoreInteger;
    Integer *currentScoreInteger;
    Integer *enemyNumberInteger;
    HealthShow *selfHealth;
    HealthShow *energyShow;
    Fraction *bulletNumberFraction;
    Fraction *mineNumberFraction;
    qint32 highScore;
    qint32 currentScore;
    qint32 enemyNumber;
    qint32 enemyBackNumber;
    qint32 waitTime;
};

#endif
