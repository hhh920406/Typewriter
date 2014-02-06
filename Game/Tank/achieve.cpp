#include "achieve.h"

Achieve::Achieve()
{
    achieveImage = new QImage(":/images/achieveBackground.png");
    destroyEnemyInteger = new Integer();
    destroyUnitInteger = new Integer();
    totalScoreInteger = new Integer();
    bulletNumberInteger = new Integer();
    mineNumberInteger = new Integer();
    stageNumberInteger = new Integer();

    this->destroyEnemyInteger->setAlign(Defination::ALIGN_RIGHT);
    this->destroyUnitInteger->setAlign(Defination::ALIGN_RIGHT);
    this->totalScoreInteger->setAlign(Defination::ALIGN_RIGHT);
    this->bulletNumberInteger->setAlign(Defination::ALIGN_RIGHT);
    this->mineNumberInteger->setAlign(Defination::ALIGN_RIGHT);
    this->stageNumberInteger->setAlign(Defination::ALIGN_RIGHT);

    this->destroyEnemyInteger->setIntegerLength(12);
    this->destroyUnitInteger->setIntegerLength(12);
    this->totalScoreInteger->setIntegerLength(12);
    this->bulletNumberInteger->setIntegerLength(12);
    this->mineNumberInteger->setIntegerLength(12);
    this->stageNumberInteger->setIntegerLength(12);
    readData();
}

Achieve::~Achieve()
{
    delete achieveImage;
    delete this->destroyEnemyInteger;
    delete this->destroyUnitInteger;
    delete this->totalScoreInteger;
    delete this->bulletNumberInteger;
    delete this->mineNumberInteger;
    delete this->stageNumberInteger;
}

void Achieve::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *achieveImage);
    this->destroyEnemyInteger->setValue(destroyEnemy);
    this->destroyUnitInteger->setValue(destroyUnit);
    this->totalScoreInteger->setValue(totalScore);
    this->bulletNumberInteger->setValue(bulletNumber);
    this->mineNumberInteger->setValue(mineNumber);
    this->stageNumberInteger->setValue(stageNumber);
    destroyEnemyInteger->draw(painter, 410, 190);
    destroyUnitInteger->draw(painter, 410, 230);
    totalScoreInteger->draw(painter, 410, 270);
    bulletNumberInteger->draw(painter, 410, 310);
    mineNumberInteger->draw(painter, 410, 350);
    stageNumberInteger->draw(painter, 410, 390);
}

void Achieve::readData()
{
    QFile file("tankSave.dat");
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QDataStream reader(&file);
        reader>>destroyEnemy>>destroyUnit>>totalScore;
        reader>>bulletNumber>>mineNumber>>stageNumber>>maxScore;
        file.close();
    }
    else
    {
        destroyEnemy = 0;
        destroyUnit = 0;
        totalScore = 0;
        bulletNumber = 0;
        mineNumber = 0;
        stageNumber = 0;
        maxScore = 0;
    }
}

void Achieve::writeData()
{
    QFile file("tankSave.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream writer(&file);
    writer<<destroyEnemy<<destroyUnit<<totalScore;
    writer<<bulletNumber<<mineNumber<<stageNumber<<maxScore;
    file.flush();
    file.close();
}

void Achieve::setDestroyEnemy(qint32 value)
{
    this->destroyEnemy = value;
}

void Achieve::setDestroyUnit(qint32 value)
{
    this->destroyUnit = value;
}

void Achieve::setTotalScore(qint32 value)
{
    this->totalScore = value;
}

void Achieve::setBulletNumber(qint32 value)
{
    this->bulletNumber = value;
}

void Achieve::setMineNumber(qint32 value)
{
    this->mineNumber = value;
}

void Achieve::setStageNumber(qint32 value)
{
    this->stageNumber = value;
}
