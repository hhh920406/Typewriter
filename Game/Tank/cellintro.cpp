#include "cellintro.h"

CellIntro::CellIntro()
{
    this->currentRole = -1;
    this->talkPosition = 0;
    this->showRole = new bool[MaxRoleNumber];
    for(qint32 i=0;i<MaxRoleNumber;i++)
    {
        this->showRole[i] = false;
    }
    this->role[0] = new QImage(":/images/zHyperG.png");
    this->role[1] = new QImage(":/images/shadowChild.png");
    this->talkBox = new QImage(":/images/talkBox.png");
    this->textArea = new TextArea();
    this->textArea->setPosition(60, 350);
    this->textArea->setSize(679, 189);
    this->cellular = new Cellular(200, 150);
    this->cellular->setSide(4);
    this->cellular->lineColor->setAlpha(0);
    for(qint32 i=50;i<=100;i++)
    {
        for(qint32 j=75;j<=125;j++)
        {
            this->cellular->opposite(i,j);
        }
    }
}

CellIntro::~CellIntro()
{
    delete this->showRole;
    for(qint32 i=0;i<MaxRoleNumber;i++)
    {
        delete this->role[i];
    }
    delete this->talkBox;
    delete this->textArea;
    delete this->cellular;
}

void CellIntro::draw(QPainter *painter)
{
    this->cellular->draw(painter);
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

qint32 CellIntro::mouseReleaseEvent()
{
    if(this->nextText())
    {
        return Defination::SCENE_CELL;
    }
    return Defination::SCENE_CELLINTRO;
}

qint32 CellIntro::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        return Defination::SCENE_CELL;
    }
    else if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Enter)
    {
        if(this->nextText())
        {
            return Defination::SCENE_CELL;
        }
    }
    return Defination::SCENE_CELLINTRO;
}

bool CellIntro::nextText()
{
    if(!this->textArea->textAll())
    {
        this->textArea->showAll();
    }
    else
    {
        this->cellular->nextGeneration();
        switch(this->talkPosition)
        {
        case 0:
            this->textArea->setText(QObject::tr("(Google Translation) Ever since, the rule here is to introduce to this forum where, if you already know the rules can press Esc to go directly."));
            break;
        case 1:
            this->showRole[1] = true;
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("Saying you are here and put a tank of this stuff is not the slightest relationship ah, do not say you just want to make this project a few more lines of code just..."));
            break;
        case 2:
            this->showRole[0] = true;
            this->currentRole = 0;
            this->textArea->setText(QObject::tr("...Ah...almost so, but the most important thing is ready there is a dialogue system, copy and paste more convenient..."));
            break;
        case 3:
            this->textArea->setText(QObject::tr("This scene and the game does not matter, is essentially a two-dimensional simulation of cellular automata, the basic rules are as follows:"));
            break;
        case 4:
            this->textArea->setText(QObject::tr("1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation. "));
            break;
        case 5:
            this->textArea->setText(QObject::tr("2. Any live cell with more than three live neighbours dies, as if by overcrowding. "));
            break;
        case 6:
            this->textArea->setText(QObject::tr("3. Any live cell with two or three live neighbours lives on to the next generation. "));
            break;
        case 7:
            this->textArea->setText(QObject::tr("4. Any dead cell with exactly three live neighbours becomes a live cell. "));
            break;
        case 8:
            this->textArea->setText(QObject::tr("Background of the presentation is now one of the initial circumstances change. "));
            break;
        case 9:
            this->textArea->setText(QObject::tr("But there is this forum so special about the boundary treatment, we assume that the upper boundary and lower boundary, left and right border are adjacent."));
            break;
        case 10:
            this->textArea->setText(QObject::tr("The next button shows: Esc to exit the forum, C empty forum, S starts the demonstration. Mouse click can change the initial cell life and death."));
            break;
        case 11:
            this->showRole[0] = false;
            this->currentRole = 1;
            this->textArea->setText(QObject::tr("Really really is no point module it..."));
            break;
        case 12:
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
