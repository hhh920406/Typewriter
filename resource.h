#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#define WINDOW_TITLE        "ZSTG 1 Memset"
#define WINDOW_WIDTH        800
#define WINDOW_HEIGHT       600
#define WINDOW_FULLSCREEN   false

enum ImageResouce
{
    RES_IMAGE_GAME_BACKGROUND,
    RES_IMAGE_BULLET,
    RES_IMAGE_LIVING
};
#define RES_IMAGE_PATH_GAME_BACKGROUND      "back.png"
#define RES_IMAGE_SIZE_GAME_BACKGROUND_W    800
#define RES_IMAGE_SIZE_GAME_BACKGROUND_H    600
#define RES_IMAGE_PATH_BULLET               "bullet.png"
#define RES_IMAGE_PATH_BULLET_W             1024
#define RES_IMAGE_PATH_BULLET_H             1024
#define RES_IMAGE_PATH_LIVING               "living.png"
#define RES_IMAGE_PATH_LIVING_W             1024
#define RES_IMAGE_PATH_LIVING_H             1024

#define RES_POS_GAME_BACKGROUND_LEFT_X      0
#define RES_POS_GAME_BACKGROUND_LEFT_Y      0
#define RES_POS_GAME_BACKGROUND_LEFT_W      50
#define RES_POS_GAME_BACKGROUND_LEFT_H      600

#define RES_POS_GAME_BACKGROUND_TOP_X       50
#define RES_POS_GAME_BACKGROUND_TOP_Y       0
#define RES_POS_GAME_BACKGROUND_TOP_W       550
#define RES_POS_GAME_BACKGROUND_TOP_H       50

#define RES_POS_GAME_BACKGROUND_BOTTOM_X    50
#define RES_POS_GAME_BACKGROUND_BOTTOM_Y    550
#define RES_POS_GAME_BACKGROUND_BOTTOM_W    550
#define RES_POS_GAME_BACKGROUND_BOTTOM_H    50

#define RES_POS_GAME_BACKGROUND_RIGHT_X     550
#define RES_POS_GAME_BACKGROUND_RIGHT_Y     0
#define RES_POS_GAME_BACKGROUND_RIGHT_W     250
#define RES_POS_GAME_BACKGROUND_RIGHT_H     600

#define RES_POS_PLAYER_X                    0
#define RES_POS_PLAYER_Y                    0
#define RES_POS_PLAYER_W                    256
#define RES_POS_PLAYER_H                    256

#define RES_SIZE_PLAYER_W                   50
#define RES_SIZE_PLAYER_H                   50

#define RES_POS_BOSS_1_X                    256
#define RES_POS_BOSS_1_Y                    0
#define RES_POS_BOSS_1_W                    256
#define RES_POS_BOSS_1_H                    256

#define RES_SIZE_BOSS_1_W                   50
#define RES_SIZE_BOSS_1_H                   50

#define RES_POS_ENEMY_1_X                   0
#define RES_POS_ENEMY_1_Y                   256
#define RES_POS_ENEMY_1_W                   256
#define RES_POS_ENEMY_1_H                   256

#define RES_POS_ENEMY_2_X                   256
#define RES_POS_ENEMY_2_Y                   256
#define RES_POS_ENEMY_2_W                   256
#define RES_POS_ENEMY_2_H                   256

#endif
