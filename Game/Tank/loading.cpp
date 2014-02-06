#include "loading.h"

Loading::Loading()
{
    image = new QImage(":/images/logo.bmp");
    background = new QImage(":/images/mainBackground.png");
    light = new QImage(":/images/light.png");
    tempImage = new QImage(image->width(), image->height(), QImage::Format_ARGB32);
    maxAlpha = false;
    stayTime = 0;
    lightTime = 0;
}

Loading::~Loading()
{
    delete image;
    delete tempImage;
    delete background;
    delete light;
}

bool Loading::draw(qint32 &time, QPainter *painter)
{
    if(maxAlpha)
    {
        painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *background);
    }
    else
    {
        painter->setBrush(Qt::white);
        painter->drawRect(0,0,Defination::WINDOW_WIDTH, Defination::WINDOW_HEIGHT);
    }
    QColor color;
    for(qint32 i=0;i<image->width();i++)
    {
        for(qint32 j=0;j<image->height();j++)
        {
            color = image->pixel(i,j);
            tempImage->setPixel(i,j,qRgba(color.red(), color.green(), color.blue(), time*4));
        }
    }
    painter->drawImage(QRect(0,0,Defination::WINDOW_WIDTH,Defination::WINDOW_HEIGHT), *tempImage);
    if(maxAlpha)
    {
        if(stayTime<20)
        {
            if(lightTime<35)
            {
                lightTime++;
                painter->drawImage( lightTime * 18, 150, *light);
            }
            else
            {
                stayTime++;
            }
        }
        else
        {
            time-=2;
            if(time<=0)
            {
                return true;
            }
        }
    }
    else
    {
        if(time++>=62)
        {
            maxAlpha=true;
        }
    }
    return false;
}
