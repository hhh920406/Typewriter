#ifndef POINT2D_H
#define POINT2D_H
/**
 * 基本的二维点。
 * @author ZHG <CyberZHG@gmail.com>
 */

class Point2D
{
public:
    Point2D();
    Point2D(const Point2D &point);
    Point2D(const float x, const float y);
    virtual ~Point2D();
    float x() const;
    float y() const;
    void setX(const float x);
    void setY(const float y);
    void setPos(const float x, const float y);

private:
    float _x;
    float _y;
};

#endif // POINT2D_H
