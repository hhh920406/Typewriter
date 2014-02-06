#include "game.h"

Game::Game()
{
    this->background = new QImage(":/images/gameBackground.png");
    this->self[Defination::DIRECTION_UP] = new QImage(":/images/selfu.png");
    this->self[Defination::DIRECTION_RIGHT] = new QImage(":/images/selfr.png");
    this->self[Defination::DIRECTION_DOWN] = new QImage(":/images/selfd.png");
    this->self[Defination::DIRECTION_LEFT] = new QImage(":/images/selfl.png");
    this->enemy1[Defination::DIRECTION_UP] = new QImage(":/images/enemy1u.png");
    this->enemy1[Defination::DIRECTION_RIGHT] = new QImage(":/images/enemy1r.png");
    this->enemy1[Defination::DIRECTION_DOWN] = new QImage(":/images/enemy1d.png");
    this->enemy1[Defination::DIRECTION_LEFT] = new QImage(":/images/enemy1l.png");
    this->bullet[Defination::DIRECTION_UP] = new QImage(":/images/bulletu.png");
    this->bullet[Defination::DIRECTION_RIGHT] = new QImage(":/images/bulletr.png");
    this->bullet[Defination::DIRECTION_DOWN] = new QImage(":/images/bulletd.png");
    this->bullet[Defination::DIRECTION_LEFT] = new QImage(":/images/bulletl.png");
    this->mine = new QImage(":/images/mine.png");
    this->catTeacherB = new QImage(":/images/catTeacherb.png");
    this->catTeacherW = new QImage(":/images/catTeacherw.png");

    this->selfTank = new Tank();
    this->selfTank->type = Defination::TYPE_SELF;
    this->selfTank->maxLife = 300;
    this->selfTank->currentLife = 300;
    this->selfTank->setPosition(220,500);
    this->selfTank->setSize(40,40);
    this->selfTank->healthShow->maxValue = 300;
    this->selfTank->healthShow->currentValue = 300;

    for(qint32 i=0;i<MaxTankNumber;i++)
    {
        this->enemyTank[i] = new Tank();
        this->enemyTank[i]->type = Defination::TYPE_ENEMY1;
        this->enemyTank[i]->setMaxLife(100);
        this->enemyTank[i]->setLife(100);
        this->enemyTank[i]->setSize(40, 40);
        this->enemyTank[i]->stay = false;
        this->enemyTank[i]->currentBulletNumber = this->enemyTank[i]->maximumBulletNumber;
        this->enemyTank[i]->decreaseCatEnergy = 0;
    }

    this->environment = new Environment();

    highScoreInteger = new Integer();
    currentScoreInteger = new Integer();
    enemyNumberInteger = new Integer();
    selfHealth = new HealthShow();
    selfHealth->maxValue = this->selfTank->maxLife;
    selfHealth->stay = true;
    selfHealth->x = 565;
    selfHealth->y = 230;
    selfHealth->width = 215;
    selfHealth->height = 25;
    this->energyShow = new HealthShow();
    this->energyShow->maxValue = this->selfTank->maxEnergy;
    this->energyShow->stay = true;
    this->energyShow->currentValue = 1;
    this->energyShow->x = 565;
    this->energyShow->y = 450;
    this->energyShow->width = 215;
    this->energyShow->height = 25;
    bulletNumberFraction = new Fraction();
    bulletNumberFraction->setIntegerLength(4);
    bulletNumberFraction->setMaxValue(this->selfTank->maximumBulletNumber);
    mineNumberFraction = new Fraction();
    mineNumberFraction->setIntegerLength(1);
    mineNumberFraction->setMaxValue(this->selfTank->maximumMineNumber);
    this->highScore = 0;
    this->currentScore = 0;
    this->enemyNumber = 20;
    this->currentStage = 1;
}

Game::~Game()
{
    delete this->background;
    for(qint32 i=0;i<4;i++)
    {
        delete this->self[i];
        delete this->enemy1[i];
        delete this->bullet[i];
    }
    for(qint32 i=0;i<MaxTankNumber;i++)
    {
        delete this->enemyTank[i];
    }
    delete this->mine;
    delete this->selfTank;
    delete this->environment;
    delete this->highScoreInteger;
    delete this->currentScoreInteger;
    delete this->enemyNumberInteger;
    delete this->selfHealth;
    delete this->energyShow;
    delete this->bulletNumberFraction;
    delete this->mineNumberFraction;
    delete this->catTeacherB;
    delete this->catTeacherW;
}

void Game::initialStage(qint32 stage)
{
    this->waitTime = 0;

    for(qint32 i=0;i<MaxTankNumber;i++)
    {
        this->enemyTank[i]->visiable = false;
        this->enemyTank[i]->setMaxLife(this->enemyTank[i]->maxLife + 10 + i);
        this->enemyTank[i]->catStatus = false;
    }
    this->selfTank->setPosition(220, 500);
    this->enemyNumber = this->currentStage + 4;
    if(this->enemyNumber > 20)
    {
        this->enemyNumber = 20;
    }
    this->enemyBackNumber = this->enemyNumber;
    this->environment->initialEnvironment();
    this->environment->initialStage(stage);

    this->selfTank->maximumBulletNumber += this->currentStage - 1;
    this->bulletNumberFraction->setMaxValue(this->selfTank->maximumBulletNumber);
    this->selfTank->currentBulletNumber += this->selfTank->maximumBulletNumber / 2 + 10;
    if(this->selfTank->currentBulletNumber > this->selfTank->maximumBulletNumber)
    {
        this->selfTank->currentBulletNumber = this->selfTank->maximumBulletNumber;
    }

    this->selfTank->currentMineNumber += 3;
    if(this->selfTank->currentMineNumber > this->selfTank->maximumMineNumber)
    {
        this->selfTank->currentMineNumber = this->selfTank->maximumMineNumber;
    }

    this->selfTank->maxLife += 10 + this->currentStage;
    this->selfHealth->maxValue = this->selfTank->maxLife;
    this->selfTank->healthShow->maxValue = this->selfTank->maxLife;
    this->selfTank->currentLife += this->selfTank->maxLife / 2;
    if(this->selfTank->currentLife > this->selfTank->maxLife)
    {
        this->selfTank->currentLife = this->selfTank->maxLife;
    }

    this->selfTank->bulletStatus = 0;
    this->selfTank->mineStatus = 0;
    this->selfTank->stay = true;
    this->selfTank->catStatus = false;
    this->selfTank->trueCatStatus = false;
}

qint32 Game::draw(QPainter *painter, qint32 &time)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *background);
    this->environment->draw(painter);
    selfTank->move(environment, enemyTank, MaxTankNumber);
    if(this->selfTank->catStatus)
    {
        selfTank->draw(painter, this->catTeacherW, bullet, mine, environment);
    }
    else
    {
        selfTank->draw(painter, self, bullet, mine, environment);
    }
    if(this->selfTank->trueCatStatus)
    {
        this->environment->trueCatPower();
        for(qint32 i=0;i<MaxTankNumber;i++)
        {
            this->enemyTank[i]->setLife(this->enemyTank[i]->currentLife - 2);
        }
    }
    for(qint32 i=0;i<MaxTankNumber;i++)
    {
        if(enemyTank[i]->move(environment, selfTank))
        {
            this->enemyNumber --;
            this->achieve->destroyEnemy ++;
            this->currentScore += enemyTank[i]->maxLife;
            this->achieve->totalScore += enemyTank[i]->maxLife;
            if(this->currentScore > this->achieve->maxScore)
            {
                this->achieve->maxScore = this->currentScore;
            }
        }
        if(enemyTank[i]->catStatus)
        {
            enemyTank[i]->draw(painter, this->catTeacherB, bullet, mine, environment);
        }
        else
        {
            enemyTank[i]->draw(painter, enemy1, bullet, mine, environment);
        }
        if(time%10==0)
        {
            enemyTank[i]->autoMove(environment, 0);
            if(!enemyTank[i]->catStatus && !this->environment->catStoneExist())
            {
                enemyTank[i]->catStatus = true;
            }
        }
        if(rand() % 300 == 0 && !enemyTank[i]->visiable && this->enemyBackNumber)
        {
            enemyTank[i]->visiable = true;
            enemyTank[i]->setLife(enemyTank[i]->maxLife);
            enemyTank[i]->healthShow->show = 0;
            enemyTank[i]->moveDirection = Defination::DIRECTION_DOWN;
            switch (rand() % 3)
            {
            case 0:
                enemyTank[i]->setPosition(60, 60);
                break;
            case 1:
                enemyTank[i]->setPosition(280, 60);
                break;
            default:
                enemyTank[i]->setPosition(500, 60);
            }
            if(this->selfTank->hitTest(enemyTank[i]->x, enemyTank[i]->y, enemyTank[i]->width, enemyTank[i]->height))
            {
                enemyTank[i]->setPosition(220, 500);
                enemyTank[i]->moveDirection = Defination::DIRECTION_UP;
                enemyTank[i]->fire();
            }
            this->enemyBackNumber --;
        }
    }
    this->highScoreInteger->setValue(this->achieve->maxScore);
    this->currentScoreInteger->setValue(this->currentScore);
    this->enemyNumberInteger->setValue(this->enemyNumber);
    this->selfHealth->setValue(this->selfTank->currentLife);
    this->energyShow->setValue(this->selfTank->energy);
    this->bulletNumberFraction->setValue(this->selfTank->currentBulletNumber);
    this->mineNumberFraction->setValue(this->selfTank->currentMineNumber);
    this->highScoreInteger->draw(painter, 645, 57);
    this->currentScoreInteger->draw(painter, 645, 105);
    this->enemyNumberInteger->draw(painter, 690, 152);
    this->selfHealth->draw(painter);
    this->energyShow->draw(painter);
    this->bulletNumberFraction->draw(painter, 585, 295);
    this->mineNumberFraction->draw(painter, 585, 375);
    time++;
    if(this->selfTank->currentLife <= 0)
    {
        this->selfTank->visiable = false;
        if(this->waitTime ++ == 50)
        {
            return Defination::SCENE_OVER;
        }
    }
    else if(this->enemyNumber == 0)
    {
        if(!this->waitTime)
        {
            this->achieve->stageNumber ++;
            this->currentScore += 1000;
            this->achieve->totalScore += 1000;
            if(this->currentScore > this->achieve->maxScore)
            {
                this->achieve->maxScore = this->currentScore;
            }
        }
        if(this->waitTime ++ == 50)
        {
            return Defination::SCENE_STAGE;
        }
    }
    return Defination::SCENE_GAME;
}

void Game::keyDown(QKeyEvent *e)
{
    if(!e->isAutoRepeat())
    {
        if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_UP]->currentKeyValue)
        {
            this->selfTank->stay = false;
            this->selfTank->moveDirection = Defination::DIRECTION_UP;
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_RIGHT]->currentKeyValue)
        {
            this->selfTank->stay = false;
            this->selfTank->moveDirection = Defination::DIRECTION_RIGHT;
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_DOWN]->currentKeyValue)
        {
            this->selfTank->stay = false;
            this->selfTank->moveDirection = Defination::DIRECTION_DOWN;
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_LEFT]->currentKeyValue)
        {
            this->selfTank->stay = false;
            this->selfTank->moveDirection = Defination::DIRECTION_LEFT;
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_FIRE]->currentKeyValue)
        {
            if(!this->selfTank->catStatus)
            {
                this->selfTank->fire();
                this->achieve->bulletNumber ++;
            }
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_MINE]->currentKeyValue)
        {
            if(!this->selfTank->catStatus)
            {
                this->selfTank->setMine();
                this->achieve->mineNumber ++;
            }
        }
    }
}

qint32 Game::keyRelease(QKeyEvent *e)
{
    if(!e->isAutoRepeat())
    {
        if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_UP]->currentKeyValue)
        {
            if(this->selfTank->moveDirection == Defination::DIRECTION_UP)
            {
                this->selfTank->stay = true;
            }
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_RIGHT]->currentKeyValue)
        {
            if(this->selfTank->moveDirection == Defination::DIRECTION_RIGHT)
            {
                this->selfTank->stay = true;
            }
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_DOWN]->currentKeyValue)
        {
            if(this->selfTank->moveDirection == Defination::DIRECTION_DOWN)
            {
                this->selfTank->stay = true;
            }
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_LEFT]->currentKeyValue)
        {
           if(this->selfTank->moveDirection == Defination::DIRECTION_LEFT)
           {
               this->selfTank->stay = true;
           }
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_PAUSE]->currentKeyValue)
        {
            return Defination::SCENE_PAUSE;
        }
        else if(e->key() == this->config->gameKeyEdit[Defination::GAMEKEY_CAT]->currentKeyValue)
        {
            this->selfTank->cat();
        }
    }
    return Defination::SCENE_GAME;
}

void Game::bindAchieve(Achieve *achieve)
{
    this->achieve = achieve;
    this->environment->bindAchieve(achieve);
}

void Game::bindConfig(Config *config)
{
    this->config = config;
}
