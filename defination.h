#ifndef DEFINATION_H_INCLUDED
#define DEFINATION_H_INCLUDED

/**
 * 子弹伤害类型。
 */
enum BulletAttackType
{
    BULLET_ATTACK_PLAYER,   // 攻击玩家的子弹
    BULLET_ATTACK_ENEMY,    // 攻击敌方的子弹
    BULLET_ATTACK_NULL = 0x7FFFFFFF
};

/**
 * 子弹类型。
 */
enum BulletType
{
    // 普通圆形子弹
    BULLET_CIRCLE_RED,
    BULLET_CIRCLE_ORANGE,
    BULLET_CIRCLE_YELLOW,
    BULLET_CIRCLE_GREEN,
    BULLET_CIRCLE_CYAN,
    BULLET_CIRCLE_BLUE,
    BULLET_CIRCLE_PURPLE,
    BULLET_CIRCLE_BLACK,
    BULLET_CIRCLE_WHITE,
    BULLET_TYPE_NULL = 0x7FFFFFFF
};

/**
 * 场景名称。
 */
enum SceneName
{
    SCENE_MAIN_MENU,    // 主菜单界面
    SCENE_GAME_LOOP,    // 游戏界面
    SCENE_NULL = 0x7FFFFFFF
};

/**
 * 游戏分层。
 */
enum GameLayer
{
    GAME_LAYER_BACK_0,      // 下层背景层
    GAME_LAYER_BACK_1,      // 上层背景层
    GAME_LAYER_ALIVE,       // 玩家与敌人层
    GAME_LAYER_BULLET_0,    // 光效子弹层
    GAME_LAYER_BULLET_1,    // 实体子弹层
    GAME_LAYER_JUDGE,       // 判定点的绘制
    GAME_LAYER_EVENT_0,     // 立绘与对话框
    GAME_LAYER_EVENT_1,     // 文字层
    GAME_LAYER_NUM,
    GAME_LAYER_NULL = 0x7FFFFFFF
};

#endif // DEFINATION_H_INCLUDED
