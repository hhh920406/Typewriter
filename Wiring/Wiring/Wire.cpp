#include "stdafx.h"
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
 * ���л���
 * @param archive �鵵����
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