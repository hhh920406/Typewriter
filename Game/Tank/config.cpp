#include "config.h"

Config::Config()
{
    this->image = new QImage(":/images/configBackground.png");
    this->gameKeyEdit[Defination::GAMEKEY_UP] = new GameKeyEdit(130, 120, 40, 40);
    this->gameKeyEdit[Defination::GAMEKEY_DOWN] = new GameKeyEdit(130, 165, 40, 40);
    this->gameKeyEdit[Defination::GAMEKEY_LEFT] = new GameKeyEdit(85, 165, 40, 40);
    this->gameKeyEdit[Defination::GAMEKEY_RIGHT] = new GameKeyEdit(175, 165, 40, 40);
    this->gameKeyEdit[Defination::GAMEKEY_FIRE] = new GameKeyEdit(150, 225, 110, 30);
    this->gameKeyEdit[Defination::GAMEKEY_MINE] = new GameKeyEdit(150, 265, 110, 30);
    this->gameKeyEdit[Defination::GAMEKEY_PAUSE] = new GameKeyEdit(150, 305, 110, 30);
    this->gameKeyEdit[Defination::GAMEKEY_CAT] = new GameKeyEdit(150, 345, 110, 30);
    this->okButton = new GameButton(":/button/ok.png",550,550);
    this->cancelButton = new GameButton(":/button/cancel.png",670,550);
}

Config::~Config()
{
    delete this->image;
    for(qint32 i=0;i<GameEditNumber;i++)
    {
        delete this->gameKeyEdit[i];
    }
    delete okButton;
    delete cancelButton;
}

qint32 Config::mouseDown(QMouseEvent *event)
{
    for(qint32 i=0;i<GameEditNumber;i++)
    {
        this->gameKeyEdit[i]->setEdit(event);
    }
    if(this->okButton->inArea(event->x(), event->y()))
    {
        this->writeInfo();
        return Defination::SCENE_MAIN;
    }
    else if(this->cancelButton->inArea(event->x(), event->y()))
    {
        return Defination::SCENE_MAIN;
    }
    return Defination::SCENE_CONFIG;
}

void Config::mouseMove(QMouseEvent *event)
{
    this->okButton->setMousePosition(event->x(), event->y());
    this->cancelButton->setMousePosition(event->x(), event->y());
    for(qint32 i=0;i<GameEditNumber;i++)
    {
        this->gameKeyEdit[i]->mouseMove(event);
    }
}

void Config::keyDown(QKeyEvent *event)
{
    for(qint32 i=0;i<GameEditNumber;i++)
    {
        this->gameKeyEdit[i]->keyDown(event);
    }
}

void Config::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *image);
    for(qint32 i=0;i<GameEditNumber;i++)
    {
        this->gameKeyEdit[i]->draw(painter);
    }
    this->okButton->draw(painter);
    this->cancelButton->draw(painter);
}

void Config::readInfo()
{
    QFile file("tankKey.conf");
    if(file.exists())
    {
        file.open(QIODevice::ReadOnly);
        QDataStream reader(&file);
        for(qint32 i=0;i<GameEditNumber;i++)
        {
            reader>>this->gameKeyEdit[i]->currentKeyValue;
        }
        file.close();
    }
    else
    {
        this->gameKeyEdit[Defination::GAMEKEY_UP]->currentKeyValue = Qt::Key_W;
        this->gameKeyEdit[Defination::GAMEKEY_DOWN]->currentKeyValue = Qt::Key_S;
        this->gameKeyEdit[Defination::GAMEKEY_LEFT]->currentKeyValue = Qt::Key_A;
        this->gameKeyEdit[Defination::GAMEKEY_RIGHT]->currentKeyValue = Qt::Key_D;
        this->gameKeyEdit[Defination::GAMEKEY_FIRE]->currentKeyValue = Qt::Key_J;
        this->gameKeyEdit[Defination::GAMEKEY_MINE]->currentKeyValue = Qt::Key_K;
        this->gameKeyEdit[Defination::GAMEKEY_PAUSE]->currentKeyValue = Qt::Key_P;
        this->gameKeyEdit[Defination::GAMEKEY_CAT]->currentKeyValue = Qt::Key_L;
        this->writeInfo();
    }
}


void Config::writeInfo()
{
    QFile file("tankKey.conf");
    file.open(QIODevice::WriteOnly);
    QDataStream writer(&file);
    for(qint32 i=0;i<GameEditNumber;i++)
    {
        writer<<this->gameKeyEdit[i]->currentKeyValue;
    }
    file.flush();
    file.close();
}
