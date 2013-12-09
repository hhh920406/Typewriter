#include "stdafx.h"
#include "Pin.h"


Pin::Pin()
{
	this->setOrientation(ORI_TOP);
	this->setShift(0.0);
}


Pin::~Pin()
{
}

void Pin::setOrientation(const Orientation orientation)
{
	this->_orientation = orientation;
}

Pin::Orientation Pin::orientation() const
{
	return this->_orientation;
}

void Pin::setShift(const double shift)
{
	this->_shift = shift;
}

double Pin::shift() const
{
	return this->_shift;
}