#include "stdafx.h"
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
 * 序列化。
 * @param archive 归档对象。
 */
void Wire::serialize(CArchive &archive)
{
	if (archive.IsStoring())
	{
		archive << this->count();
		for (int i = 0; i < this->count(); ++i)
		{
			archive << this->x(i) << this->y(i);
		}
		archive << this->u() << this->v();
	}
	else
	{
		unsigned int size;
		archive >> size;
		this->_x.clear();
		this->_y.clear();
		for (unsigned int i = 0; i < size; ++i)
		{
			double tx, ty;
			archive >> tx >> ty;
			this->add(tx, ty);
		}
		archive >> this->_u >> this->_v;
	}
}