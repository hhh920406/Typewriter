#ifndef ACHIEVE_H
#define ACHIEVE_H

#include <QImage>
#include <QPainter>
#include <QFile>
#include <QDataStream>
#include "defination.h"
#include "integer.h"

class Achieve
{
public:
    Achieve();
    ~Achieve();
    void readData();
    void writeData();
    void draw(QPainter *painter);
    void setDestroyEnemy(qint32 value);
    void setDestroyUnit(qint32 value);
    void setTotalScore(qint32 value);
    void setBulletNumber(qint32 value);
    void setMineNumber(qint32 value);
    void setStageNumber(qint32 value);

    qint64 destroyEnemy;
    qint64 destroyUnit;
    qint64 totalScore;
    qint64 bulletNumber;
    qint64 mineNumber;
    qint64 stageNumber;
    qint64 maxScore;
private:
    QImage *achieveImage;
    Integer *destroyEnemyInteger;
    Integer *destroyUnitInteger;
    Integer *totalScoreInteger;
    Integer *bulletNumberInteger;
    Integer *mineNumberInteger;
    Integer *stageNumberInteger;
};
#endif
