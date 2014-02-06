#include "mainmenu.h"

MainMenu::MainMenu()
{
    background = new QImage(":/images/mainBackground.png");
    startButton = new GameButton(":/button/start.png",900,220);
    achieveButton = new GameButton(":/button/achieve.png",880,280);
    helpButton = new GameButton(":/button/help.png",860,340);
    configButton = new GameButton(":/button/config.png",840,400);
    exitButton = new GameButton(":/button/close.png",820,460);
    startButton->enabled = false;
    achieveButton->enabled = false;
    helpButton->enabled = false;
    configButton->enabled = false;
    exitButton->enabled = false;
    targetX[0] = 270;
    targetX[1] = 240;
    targetX[2] = 280;
    targetX[3] = 340;
    targetX[4] = 440;
}

MainMenu::~MainMenu()
{
    delete background;
    delete startButton;
    delete achieveButton;
    delete helpButton;
    delete configButton;
    delete exitButton;
}

qint32 MainMenu::click(qint32 x, qint32 y)
{
    if(startButton->inArea(x,y)) return Defination::SCENE_CHOICE;
    if(achieveButton->inArea(x,y)) return Defination::SCENE_ACHIEVE;
    if(helpButton->inArea(x,y)) return Defination::SCENE_HELP;
    if(configButton->inArea(x,y)) return Defination::SCENE_CONFIG;
    if(exitButton->inArea(x,y)) return Defination::SCENE_CLOSE;
    return Defination::SCENE_MAIN;
}

void MainMenu::setMousePosition(qint32 x, qint32 y)
{
    startButton->setMousePosition(x,y);
    achieveButton->setMousePosition(x,y);
    helpButton->setMousePosition(x,y);
    configButton->setMousePosition(x,y);
    exitButton->setMousePosition(x,y);
}

void MainMenu::draw(QPainter *painter)
{
    painter->setBrush(Qt::white);
    painter->drawRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT);
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *background);
    startButton->draw(painter);
    achieveButton->draw(painter);
    helpButton->draw(painter);
    configButton->draw(painter);
    exitButton->draw(painter);
    if(startButton->x > targetX[0]) startButton->x -= 8;
    else if(startButton->x < targetX[0]) startButton->x += 1;
    else startButton->enabled = true;
    if(achieveButton->x > targetX[1]) achieveButton->x -= 8;
    else if(achieveButton->x < targetX[1]) achieveButton->x += 1;
    else achieveButton->enabled = true;
    if(helpButton->x > targetX[2]) helpButton->x -= 8;
    else if(helpButton->x < targetX[2]) helpButton->x += 1;
    else helpButton->enabled = true;
    if(configButton->x > targetX[3]) configButton->x -= 8;
    else if(configButton->x < targetX[3]) configButton->x += 1;
    else configButton->enabled = true;
    if(exitButton->x > targetX[4]) exitButton->x -= 8;
    else if(exitButton->x < targetX[4]) exitButton->x += 1;
    else exitButton->enabled = true;
}

void MainMenu::moveToPosition()
{
    if(!this->startButton->enabled)
    {
        this->startButton->x = this->targetX[0];
        this->achieveButton->x = this->targetX[1];
        this->helpButton->x = this->targetX[2];
        this->configButton->x = this->targetX[3];
        this->exitButton->x = this->targetX[4];
    }
}
