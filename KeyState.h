#ifndef KEYSTATE_H
#define KEYSTATE_H

#include <vector>
#include <windows.h>

class KeyState
{
public:
    enum Key
    {
        KEY_Z,
        KEY_X,
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_ENTER,
        KEY_SHIFT,
        KEY_CTRL,
        KEY_ESCAPE,
        KEY_UNKNOWN
    };
    KeyState();
    virtual ~KeyState();
    void press(const Key key);
    void release(const Key key);
    bool isPressed(const Key key);
    static Key convertKey(WPARAM wParam);

private:
    std::vector<bool> _pressed;
};

#endif
