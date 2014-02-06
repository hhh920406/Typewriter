#include "stdafx.h"
#include <cmath>
#include "Wire.h"
using namespace std;

/**
 * ���캯����Ĭ�ϵĽڵ���Ϊ0��
 */
Wire::Wire()
{
}


Wire::~Wire()
{
}

/**
 * Ϊ��������µĽڵ㡣
 * @param x �½ڵ�ĺ����ꡣ
 * @param y �½ڵ�������ꡣ
 */
void Wire::add(const double x, const double y)
{
    this->_x.push_back(x);
    this->_y.push_back(y);
}

/**
 * �Ƴ�ָ��λ�õĽڵ㡣
 * @param index Ҫ�Ƴ��Ľڵ���±꣬������Ϸ��򲻽��в�����
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
 * ��ȡ�ڵ����Ŀ��
 * @return �ڵ����Ŀ��
 */
int Wire::count() const
{
    return this->_x.size();
}

/**
 * ����ָ��λ�õĽڵ�����ꡣ
 * @param index Ҫ����Ľڵ���±ꡣ
 * @param x �µĺ����ꡣ
 * @param y �µ������ꡣ
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
 * ��ȡ�����ꡣ
 * @param Ҫ��ȡ�Ľڵ���±ꡣ
 * @return �����ꡣ
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
 * ��ȡ�����ꡣ
 * @param Ҫ��ȡ�Ľڵ���±ꡣ
 * @return �����ꡣ
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
 * �������ߵ����ŵı�š�
 * @param u ���ű�š�
 */
void Wire::setU(const int u)
{
    this->_u = u;
}

/**
 * �������ߵ����ŵı�š�
 * @param v ���ű�š�
 */
void Wire::setV(const int v)
{
    this->_v = v;
}

/**
 * �������ŵı�š�
 * @return ���ű�š�
 */
int Wire::u() const
{
    return this->_u;
}

/**
 * �������ŵı�š�
 * @return ���ű�š�
 */
int Wire::v() const
{
    return this->_v;
}

/**
 * ��ȡ���ߵ��ܳ��ȡ�
 * @return �ܳ��ȡ�
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
 * ��ȡ�߶��ϵĵ㡣
 * @param ������ĳ������ܳ��ȵı�ֵ��
 * @return �߶��ϵĵ㡣
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