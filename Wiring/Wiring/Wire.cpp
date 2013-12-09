#include "stdafx.h"
#include "Wire.h"
using namespace std;

Wire::Wire()
{
}


Wire::~Wire()
{
}

void Wire::addNode(const double x, const double y)
{
	this->_x.push_back(x);
	this->_y.push_back(y);
}

void Wire::removeNode(int index)
{
	if (index >= 0 && index < this->_x.size())
	{
		this->_x.erase(this->_x.begin() + index);
		this->_y.erase(this->_y.begin() + index);
	}
}

int Wire::nodeNum() const
{
	return this->_x.size();
}

void Wire::setNode(const int index, const double x, const double y)
{
	if (index >= 0 && index < this->_x.size())
	{
		this->_x[index] = x;
		this->_y[index] = y;
	}
}

double Wire::getX(const int index) const
{
	if (index >= 0 && index < this->_x.size())
	{
		return this->_x[index];
	}
	return 0.0;
}

double Wire::getY(const int index) const
{
	if (index >= 0 && index < this->_y.size())
	{
		return this->_y[index];
	}
	return 0.0;
}