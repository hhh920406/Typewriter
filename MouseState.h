#ifndef MOUSESTATE_H
#define MOUSESTATE_H
/**
 * 记录鼠标的状态。
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "Point2D.h"

class MouseState
{
public:
    enum Key
    {
        KEY_LEFT,
        KEY_RIGHT,
        KEY_MIDDLE
    };
    MouseState();
    virtual ~MouseState();

    void press(const Key key);
    void release(const Key key);
    bool isPressed(const Key key);

    void setPos(const int x, const int y);
    int x() const;
    int y() const;
    const Point2D pos() const;

private:
    bool _pressed[3];
    Point2D _pos;
};

#endif // MOUSESTATE_H
