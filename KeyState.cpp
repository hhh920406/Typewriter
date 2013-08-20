#include "KeyState.h"
using namespace std;

KeyState::KeyState()
{
    for (int i = 0; i < KEY_TOTAL; ++i)
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
