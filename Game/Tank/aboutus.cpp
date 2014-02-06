#include "aboutus.h"

AboutUs::AboutUs()
{
    this->currentRole = -1;
    this->talkPosition = 0;
    this->showRole = new bool[MaxRoleNumber];
    for(qint32 i=0;i<MaxRoleNumber;i++)
    {
        this->showRole[i] = false;
    }
    this->background = new QImage(":/images/aboutBackground.png");
    this->role[0] = new QImage(":/images/zHyperG.png");
    this->role[1] = new QImage(":/images/shadowChild.png");
    this->talkBox = new QImage(":/images/talkBox.png");
    this->textArea = new TextArea();
    this->textArea->setPosition(60, 350);
    this->textArea->setSize(679, 189);
}

AboutUs::~AboutUs()
{
    delete this->showRole;
    delete this->background;
    for(qint32 i=0;i<MaxRoleNumber;i++)
    {
        delete this->role[i];
    }
    delete this->talkBox;
    delete this->textArea;
}

void AboutUs::draw(QPainter *painter)
{
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT),*this->background);
    if(this->showRole[0])
    {
        painter->drawImage(100, 100, *this->role[0]);
    }
    if(this->showRole[1])
    {
        painter->drawImage(490, 150, *this->role[1]);
    }
    painter->drawImage(60, 350, *this->talkBox);
    switch(this->currentRole)
    {
    case 0:
        painter->setPen(Qt::blue);
        break;
    case 1:
        painter->setPen(Qt::darkMagenta);
        break;
    default:
        painter->setPen(Qt::black);
        break;
    }
    this->textArea->draw(painter);
}

qint32 AboutUs::mouseReleaseEvent()
{
    if(this->nextText())
    {
        return Defination::SCENE_MAIN;
    }
    return Defination::SCENE_ABOUT;
}

qint32 AboutUs::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        return Defination::SCENE_MAIN;
    }
    else if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Enter)
    {
        if(this->nextText())
        {
            return Defination::SCENE_MAIN;
        }
    }
    return Defination::SCENE_ABOUT;
}

bool AboutUs::nextText()
{
    if(!this->textArea->textAll())
    {
        this->textArea->showAll();
    }
    else
    {
        switch(this->talkPosition)
        {
        case 0:
            this->textArea->setText(QObject::tr("(Google Translation) He stood, the center of the blue world."));
            break;
        case 1:
            this->textArea->setText(QObject::tr("Everywhere you looked, the vast expanse of the ocean."));
            break;
        case 2:
            this->textArea->setText(QObject::tr("May the sun is emitting a dazzling light."));
            break;
        case 3:
            this->textArea->setText(QObject::tr("Head, the spread of the cloudless sunny sky."));
            break;
        case 4:
            this->textArea->setText(QObject::tr("Blue dripping scene, the worth of beautiful, breathtaking."));
            break;
        case 5:
            this->textArea->setText(QObject::tr("All this occupied all his attention."));
            break;
        case 6:
            this->textArea->setText(QObject::tr("Endless horizon, the sea and sky looming separation."));
            break;
        case 7:
            this->textArea->setText(QObject::tr("Has been seagulls, leisurely arc to draw beautiful, moving with the rhythm of the wind, slowly fly to afar."));
            break;
        case 8:
            this->textArea->setText(QObject::tr("Sihai breeze with a taste and gently blowing."));
            break;
        case 9:
            this->textArea->setText(QObject::tr("Behind the bustling crowd."));
            break;
        case 10:
            this->showRole[1] = true;
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("... ... ... ..."));
            break;
        case 11:
            this->textArea->setText(QObject::tr("This Galgame beginning in the end is the same as what..."));
            break;
        case 12:
            this->textArea->setText(QObject::tr("But here What kind of ocean ah, it's clear that only a strange river..."));
            break;
        case 13:
            this->textArea->setText(QObject::tr("Anyway, I was who? If unwittingly entered this strange world..."));
            break;
        case 14:
            this->showRole[0] = true;
            this->currentRole = 0;
            this->textArea->setText(QObject::tr("Oh ~"));
            break;
        case 15:
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("...Why a person feels heard the sinister sound of it..."));
            break;
        case 16:
            this->textArea->setText(QObject::tr("I stand and why only one person painted the outline of it..."));
            break;
        case 17:
            this->currentRole = 0;
            this->textArea->setText(QObject::tr("~ ~ There is no art because the programmers who are lonely ~ ~"));
            break;
        case 18:
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("...Who are you?"));
            break;
        case 19:
            this->currentRole = 0;
            this->textArea->setText(QObject::tr("I was the creator of the world."));
            break;
        case 20:
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("Then I wonder why in this place?"));
            break;
        case 21:
            this->currentRole = 0;
            this->textArea->setText(QObject::tr("Well, in fact, in order to achieve such a dialogue, the plot and forced to pull something that can only engage in dialogue."));
            break;
        case 22:
            this->textArea->setText(QObject::tr("How to say, this game does not exist as a formal game, the game just to make other test tools."));
            break;
        case 23:
            this->textArea->setText(QObject::tr("But you do not have low self-esteem you, maybe you outline is the next generation of it - actor"));
            break;
        case 24:
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("... ... ... ..."));
            break;
        case 25:
            this->textArea->setText(QObject::tr("And you did not actually call this place game of the scene selection screen in the game..."));
            break;
        case 26:
            this->currentRole = 0;
            this->textArea->setText(QObject::tr("Of course, think so, adding in the game like this plot is the first time, ah, hard-coded complete application, written quite Leia."));
            break;
        case 27:
            this->textArea->setText(QObject::tr("With the escalation of the game short, this part should also change it."));
            break;
        case 28:
            this->textArea->setText(QObject::tr("The current goal is to barrage STG game production and game engine production, but art and music and voice so still no idea ah."));
            break;
        case 29:
            this->textArea->setText(QObject::tr("Well, so, this is over."));
            break;
        case 30:
            this->showRole[0] = false;
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("This is too short it, it really only exists as the other games produced a..."));
            break;
        case 31:
            this->showRole[1] = false;
            this->textArea->setText("");
            break;
        default:
            return true;
        }
        this->talkPosition ++;
    }
    return false;
}
