#ifndef KEYSTATE_H
#define KEYSTATE_H
/**
 * 记录键盘按键的状态。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <vector>

class KeyState
{
public:
    enum Key
    {
        KEY_Z,
        KEY_X,
        KEY_SHIFT,
        KEY_CTRL,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_ENTER,
        KEY_ESCAPE,
        KEY_TOTAL
    };
    KeyState();
    virtual ~KeyState();
    void press(const Key key);
    void release(const Key key);
    bool isPressed(const Key key);

private:
    std::vector<bool> _pressed;
};

#endif // KEYSTATE_H
