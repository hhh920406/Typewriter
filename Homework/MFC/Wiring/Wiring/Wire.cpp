#include "stdafx.h"
#include <cmath>
#include "Wire.h"
using namespace std;

/**
 * 构造函数。默认的节点数为0。
 */
Wire::Wire()
{
}


Wire::~Wire()
{
}

/**
 * 为连线添加新的节点。
 * @param x 新节点的横坐标。
 * @param y 新节点的纵坐标。
 */
void Wire::add(const double x, const double y)
{
    this->_x.push_back(x);
    this->_y.push_back(y);
}

/**
 * 移除指定位置的节点。
 * @param index 要移除的节点的下标，如果不合法则不进行操作。
 */
void Wire::remove(unsigned int index)
{
    if (index < this->_x.size())
    {
        this->_x.erase(this->_x.begin() + index);
        this->_y.erase(this->_y.begin() + index);
    }
}

/**
 * 获取节点的数目。
 * @return 节点的数目。
 */
int Wire::count() const
{
    return this->_x.size();
}

/**
 * 设置指点位置的节点的坐标。
 * @param index 要变更的节点的下标。
 * @param x 新的横坐标。
 * @param y 新的纵坐标。
 */
void Wire::set(const unsigned int index, const double x, const double y)
{
    if (index < this->_x.size())
    {
        this->_x[index] = x;
        this->_y[index] = y;
    }
}

/**
 * 获取横坐标。
 * @param 要获取的节点的下标。
 * @return 横坐标。
 */
double Wire::x(const unsigned int index) const
{
    if (index < this->_x.size())
    {
        return this->_x[index];
    }
    return 0.0;
}

/**
 * 获取纵坐标。
 * @param 要获取的节点的下标。
 * @return 纵坐标。
 */
double Wire::y(const unsigned int index) const
{
    if (index < this->_y.size())
    {
        return this->_y[index];
    }
    return 0.0;
}

/**
 * 设置连线的引脚的编号。
 * @param u 引脚编号。
 */
void Wire::setU(const int u)
{
    this->_u = u;
}

/**
 * 设置连线的引脚的编号。
 * @param v 引脚编号。
 */
void Wire::setV(const int v)
{
    this->_v = v;
}

/**
 * 返回引脚的编号。
 * @return 引脚编号。
 */
int Wire::u() const
{
    return this->_u;
}

/**
 * 返回引脚的编号。
 * @return 引脚编号。
 */
int Wire::v() const
{
    return this->_v;
}

/**
 * 获取连线的总长度。
 * @return 总长度。
 */
double Wire::length() const
{
    double len = 0.0;
    for (unsigned int i = 0; i < this->_x.size() - 1; ++i)
    {
        len += length(i);
    }
    return len;
}

double Wire::length(const unsigned int index) const
{
    return sqrt((this->_x[index + 1] - this->_x[index]) * (this->_x[index + 1] - this->_x[index]) +
        (this->_y[index + 1] - this->_y[index]) * (this->_y[index + 1] - this->_y[index]));
}

/**
 * 获取线段上的点。
 * @param 点距起点的长度与总长度的比值。
 * @return 线段上的点。
 */
CPoint Wire::getSegmentPoint(double seg) const
{
    double total = this->length();
    double len = total * seg;
    unsigned int i;
    for (i = 0; i < this->_x.size() - 1; ++i)
    {
        double tempLen = this->length(i);
        if (len > tempLen)
        {
            len -= tempLen;
        }
        else
        {
            break;
        }
    }
    if (i == this->_x.size() - 1)
    {
        --i;
    }
    seg = len / this->length(i);
    return CPoint((int)(this->_x[i] + seg * (this->_x[i + 1] - this->_x[i])), 
        (int)(this->_y[i] + seg * (this->_y[i + 1] - this->_y[i])));
}