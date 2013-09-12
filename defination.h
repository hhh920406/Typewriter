#ifndef DEFINATION_H_INCLUDED
#define DEFINATION_H_INCLUDED

/**
 * 对窗口属性的定义。
 */
#define WINDOW_TITLE "ZSTG 1 Memset"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum SceneName
{
    SCENE_MAIN_MENU,    // 主菜单界面
    SCENE_GAME_LOOP,    // 游戏界面
    SCENE_NULL = 0x7FFFFFFF
};

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
    GAME_LAYER_NULL = 0x7FFFFFFF
};

#endif // DEFINATION_H_INCLUDED
