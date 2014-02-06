#include "cellular.h"

Cellular::Cellular(qint32 widthNumber, qint32 heightNumber)
{
    this->x = 0;
    this->y = 0;
    this->widthNumber = widthNumber;
    this->heightNumber = heightNumber;
    this->cellArea = new bool*[this->heightNumber];
    this->cellCount = new qint32*[this->heightNumber];
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        this->cellArea[i] = new bool[this->widthNumber];
        this->cellCount[i] = new qint32[this->widthNumber];
    }
    this->side = 10;
    this->liveColor = new QColor(98, 153 ,6);
    this->deadColor = new QColor(247, 202, 128);
    this->lineColor = new QColor(255, 255, 255, 200);
    this->showGenerationNumber = false;
    this->clear();
}

Cellular::~Cellular()
{
    delete this->cellArea;
    delete this->cellCount;
    delete this->lineColor;
    delete this->deadColor;
    delete this->lineColor;
}

void Cellular::setPosition(qint32 x, qint32 y)
{
    this->x = x;
    this->y = y;
}

void Cellular::setSide(qint32 side)
{
    this->side = side;
}

void Cellular::draw(QPainter *painter)
{
    painter->setPen(*this->lineColor);
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        for(qint32 j=0;j<this->widthNumber;j++)
        {
            if(this->cellArea[i][j])
            {
                painter->setBrush(*this->liveColor);
            }
            else
            {
                painter->setBrush(*this->deadColor);
            }
            painter->drawRect(this->y + j * this->side, this->x + i * this->side, side, side);
        }
    }
    if(this->showGenerationNumber)
    {
        painter->setPen(Qt::black);
        char s[100];
        sprintf(s, "Generation: %d", this->generationNumber);
        painter->drawText(20, 20, s);
    }
}

void Cellular::nextGeneration()
{
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        for(qint32 j=0;j<this->widthNumber;j++)
        {
            this->cellCount[i][j] = this->cellArea[i][(j+1)%this->widthNumber] +
                                    this->cellArea[i][(j+this->widthNumber-1)%this->widthNumber] +
                                    this->cellArea[(i+1)%this->heightNumber][(j+1)%this->widthNumber] +
                                    this->cellArea[(i+this->heightNumber-1)%this->heightNumber][(j+this->widthNumber-1)%this->widthNumber] +
                                    this->cellArea[(i+1)%this->heightNumber][j] +
                                    this->cellArea[(i+this->heightNumber-1)%this->heightNumber][j] +
                                    this->cellArea[(i+1)%this->heightNumber][(j+this->widthNumber-1)%this->widthNumber] +
                                    this->cellArea[(i+this->heightNumber-1)%this->heightNumber][(j+1)%this->widthNumber];
        }
    }
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        for(qint32 j=0;j<this->widthNumber;j++)
        {
            if(this->cellArea[i][j])
            {
                if(this->cellCount[i][j] != 2 && this->cellCount[i][j] != 3)
                {
                    this->cellArea[i][j] = false;
                }
            }
            else
            {
                if(this->cellCount[i][j] == 3)
                {
                    this->cellArea[i][j] = true;
                }
            }
        }
    }
    this->generationNumber ++;
}

void Cellular::opposite(qint32 x, qint32 y)
{
    if(x<0 || x>=this->heightNumber)
    {
        return;
    }
    if(y<0 || y>=this->widthNumber)
    {
        return;
    }
    this->cellArea[x][y] ^= 1;
}

void Cellular::clear()
{
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        for(qint32 j=0;j<this->widthNumber;j++)
        {
            this->cellArea[i][j] = false;
        }
    }
    this->generationNumber = 0;
}

void Cellular::randomInitial()
{
    this->clear();
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        for(qint32 j=0;j<this->widthNumber;j++)
        {
            this->cellArea[i][j] = rand() & 1;
        }
    }
}

void Cellular::linearInitial()
{
    this->clear();
    for(qint32 i=0;i<this->heightNumber;i++)
    {
        for(qint32 j=0;j<this->widthNumber;j++)
        {
            if(!((i+j)&3))
            {
                this->cellArea[i][j] = true;
            }
        }
    }
}
