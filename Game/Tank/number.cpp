#include "number.h"

Number::Number()
{
    char s[] = ":/images/num0.png";
    for(qint32 i=0;i<10;i++)
    {
        numImage[i] = new QImage(s);
        s[12]++;
    }
}

Number::~Number()
{
    for(qint32 i=0;i<10;i++)
    {
        delete numImage[i];
    }
}

void Number::draw(QPainter *painter, qint32 x, qint32 y, qint32 number)
{
    if(number>=0 && number<=9)
    {
        painter->drawImage(x,y,*numImage[number]);
    }
}
