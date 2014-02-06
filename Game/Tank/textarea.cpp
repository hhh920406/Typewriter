#include "textarea.h"

TextArea::TextArea()
{
    this->x = 0;
    this->y = 0;
    this->width = 100;
    this->height = 100;
    this->text = "";
    this->time = 0;
    this->textPosition = 0;
}

void TextArea::draw(QPainter *painter)
{
    painter->setFont(QFont("Consolas", 18));
    qint32 tempX = this->x + 20;
    qint32 tempY = this->y + 40;
    for(qint32 i=0;i<this->textPosition;i++)
    {
        painter->drawText(tempX, tempY, QString(this->text[i]));
        if(this->text[i] < 256)
        {
            tempX += 13;
        }
        else
        {
            tempX += 26;
        }
        if(tempX + 26 > this->x + this->width - 20)
        {
            tempX = this->x + 20;
            tempY += 30;
        }
    }
    if(!this->textAll())
    {
        this->textPosition ++;
    }
}

bool TextArea::textAll()
{
    return this->textPosition == this->text.length();
}

void TextArea::setText(QString text)
{
    this->text = text;
    this->textPosition = 0;
}

void TextArea::showAll()
{
    this->textPosition = this->text.length();
}
