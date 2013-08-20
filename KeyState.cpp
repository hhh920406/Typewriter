#include "KeyState.h"
using namespace std;

KeyState::KeyState()
{
    for (int i = 0; i < KEY_UNKNOWN; ++i)
    {
        this->_pressed.push_back(false);
    }
}

KeyState::~KeyState()
{
}

void KeyState::press(const Key key)
{
    this->_pressed[key] = true;
}

void KeyState::release(const Key key)
{
    this->_pressed[key] = false;
}

bool KeyState::isPressed(const Key key)
{
    return this->_pressed[key];
}

KeyState::Key KeyState::convertKey(WPARAM wParam)
{
    switch (wParam)
    {
    case 'Z':
        return KEY_Z;
    case 'X':
        return KEY_X;
    case VK_UP:
        return KEY_UP;
    case VK_DOWN:
        return KEY_DOWN;
    case VK_LEFT:
        return KEY_LEFT;
    case VK_RIGHT:
        return KEY_RIGHT;
    case VK_RETURN:
        return KEY_ENTER;
    case VK_SHIFT:
        return KEY_SHIFT;
    case VK_CONTROL:
        return KEY_CTRL;
    case VK_ESCAPE:
        return KEY_ESCAPE;
    default:
        return KEY_UNKNOWN;
    }
}
