#include "stdafx.h"
#include "Wire.h"
using namespace std;

Wire::Wire()
{
}


Wire::~Wire()
{
}

void Wire::add(const double x, const double y)
{
	this->_x.push_back(x);
	this->_y.push_back(y);
}

void Wire::remove(unsigned int index)
{
	if (index < this->_x.size())
	{
		this->_x.erase(this->_x.begin() + index);
		this->_y.erase(this->_y.begin() + index);
	}
}

int Wire::count() const
{
	return this->_x.size();
}

void Wire::set(const unsigned int index, const double x, const double y)
{
	if (index < this->_x.size())
	{
		this->_x[index] = x;
		this->_y[index] = y;
	}
}

double Wire::x(const unsigned int index) const
{
	if (index < this->_x.size())
	{
		return this->_x[index];
	}
	return 0.0;
}

double Wire::y(const unsigned int index) const
{
	if (index < this->_y.size())
	{
		return this->_y[index];
	}
	return 0.0;
}

void Wire::setU(const unsigned int u)
{
	this->_u = u;
}

void Wire::setV(const unsigned int v)
{
	this->_v = v;
}

unsigned int Wire::u() const
{
	return this->_u;
}

unsigned int Wire::v() const
{
	return this->_v;
}

void Wire::Serialize(CArchive &archive)
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
		int size;
		archive >> size;
		this->_x.clear();
		this->_y.clear();
		for (int i = 0; i < size; ++i)
		{
			double tx, ty;
			archive >> tx >> ty;
			this->add(tx, ty);
		}
		archive >> this->_u >> this->_v;
	}
}