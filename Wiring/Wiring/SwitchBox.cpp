#include "stdafx.h"
#include "SwitchBox.h"
using namespace std;

SwitchBox::SwitchBox()
{
}


SwitchBox::~SwitchBox()
{
}

void SwitchBox::setTitle(const CStringW &title)
{
	this->_title = title;
}

CStringW SwitchBox::title() const
{
	return this->_title;
}

void SwitchBox::setSize(const double width, const double height)
{
	this->_width = width;
	this->_height = height;
}

double SwitchBox::width() const
{
	return this->_width;
}

double SwitchBox::height() const
{
	return this->_height;
}

vector<Pin>& SwitchBox::pin()
{
	return this->_pin;
}

vector<Wire>& SwitchBox::wire()
{
	return this->_wire;
}

void SwitchBox::serialize(CArchive &archive)
{
	if (archive.IsStoring())
	{
		archive << this->_title;
		archive << this->_width << this->_height;
		archive << this->_pin.size();
		for (unsigned int i = 0; i < this->_pin.size(); ++i)
		{
			this->_pin[i].serialize(archive);
		}
		archive << this->_wire.size();
		for (unsigned int i = 0; i < this->_wire.size(); ++i)
		{
			this->_wire[i].serialize(archive);
		}
	}
	else
	{
		unsigned int size;
		archive >> this->_title;
		archive >> this->_width >> this->_height;
		archive >> size;
		this->_pin.clear();
		for (unsigned int i = 0; i < size; ++i)
		{
			Pin pin;
			pin.serialize(archive);
			this->_pin.push_back(pin);
		}
		this->_wire.clear();
		for (unsigned int i = 0; i < size; ++i)
		{
			Wire wire;
			wire.serialize(archive);
			this->_wire.push_back(wire);
		}
	}
}