#ifndef DEFINATION_H
#define DEFINATION_H

#include <QString>

class Defination
{
public:
    static const qint32 SCENE_OPENING = 0;
    static const qint32 SCENE_MAIN = 1;
    static const qint32 SCENE_ACHIEVE = 2;
    static const qint32 SCENE_HELP = 3;
    static const qint32 SCENE_GAME = 4;
    static const qint32 SCENE_CLOSE = 5;
    static const qint32 SCENE_PAUSE = 6;
    static const qint32 SCENE_STAGE = 7;
    static const qint32 SCENE_OVER = 8;
    static const qint32 SCENE_CONFIG = 9;
    static const qint32 SCENE_CHOICE = 10;
    static const qint32 SCENE_ABOUT = 11;
    static const qint32 SCENE_SNAKE = 12;
    static const qint32 SCENE_CELLINTRO = 13;
    static const qint32 SCENE_CELL = 14;

    static const qint32 WINDOW_WIDTH = 800;
    static const qint32 WINDOW_HEIGHT = 600;

    static const qint32 ALIGN_LEFT = 0;
    static const qint32 ALIGN_MIDDLE = 1;
    static const qint32 ALIGN_RIGHT = 2;

    static const qint32 TYPE_NULL = 0;
    static const qint32 TYPE_SELF = 1;
    static const qint32 TYPE_ENEMY1 = 2;
    static const qint32 TYPE_BRICK = 3;
    static const qint32 TYPE_RIVER = 4;
    static const qint32 TYPE_STEEL = 5;
    static const qint32 TYPE_MINE = 6;
    static const qint32 TYPE_BULLET = 7;
    static const qint32 TYPE_CATSTONE = 8;

    static const qint32 DIRECTION_UP = 0;
    static const qint32 DIRECTION_RIGHT = 1;
    static const qint32 DIRECTION_DOWN = 2;
    static const qint32 DIRECTION_LEFT = 3;

    static const qint32 GAMEKEY_UP = 0;
    static const qint32 GAMEKEY_RIGHT = 1;
    static const qint32 GAMEKEY_DOWN = 2;
    static const qint32 GAMEKEY_LEFT = 3;
    static const qint32 GAMEKEY_FIRE = 4;
    static const qint32 GAMEKEY_MINE = 5;
    static const qint32 GAMEKEY_PAUSE = 6;
    static const qint32 GAMEKEY_CAT = 7;
};

#endif
