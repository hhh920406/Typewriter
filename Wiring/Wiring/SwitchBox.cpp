#include "stdafx.h"
#include "SwitchBox.h"
using namespace std;

SwitchBox::SwitchBox()
{
}


SwitchBox::~SwitchBox()
{
}

/**
 * 设置布线盒的标题。
 * @param title 标题。
 */
void SwitchBox::setTitle(const CStringW &title)
{
	this->_title = title;
}

/**
 * 返回布线盒的标题。
 * @return 标题。
 */
CStringW SwitchBox::title() const
{
	return this->_title;
}

/**
 * 设置布线盒的大小。
 * @param width 宽度。
 * @param height 高度。
 */
void SwitchBox::setSize(const double width, const double height)
{
	this->_width = width;
	this->_height = height;
}

/**
 * 返回布线盒的宽度。
 * @return 宽度。
 */
double SwitchBox::width() const
{
	return this->_width;
}

/**
 * 返回布线盒的高度。
 * @return 高度。
 */
double SwitchBox::height() const
{
	return this->_height;
}

/**
 * 返回引脚的向量。
 * @return 引脚。
 */
vector<Pin>& SwitchBox::pin()
{
	return this->_pin;
}

/**
 * 返回连线的向量。
 * @return 连线。
 */
vector<Wire>& SwitchBox::wire()
{
	return this->_wire;
}

/**
 * 设置引脚的数量，围绕布线盒均匀分布。
 * @param pinNum 引脚的数量。
 */
void SwitchBox::setPinNum(const int pinNum)
{
	int hor = (int)(pinNum * this->_width / (this->_width + this->_height));
	int ver = pinNum - hor;
	int top = hor >> 1;
	int bottom = hor - top;
	int left = ver >> 1;
	int right = ver - left;
	int id = 0;
	this->_wire.clear();
	this->_pin.clear();
	double margin = this->_width / (top + 1);
	for (int i = 1; i <= top; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_TOP);
		pin.setShift(i * margin);
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
	margin = this->_height / (right + 1);
	for (int i = 1; i <= right; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_RIGHT);
		pin.setShift(i * margin);
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
	margin = this->_width / (bottom + 1);
	for (int i = 0; i < bottom; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_BOTTOM);
		pin.setShift((bottom - i) * margin);
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
	margin = this->_height / (left + 1);
	for (int i = 0; i < left; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_LEFT);
		pin.setShift((left - i) * margin);
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
}

/**
 * 序列化。
 * @param archive 归档对象。
 */
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