#include "stdafx.h"
#include "SwitchBox.h"
using namespace std;

const int PADDING = 3;
const int PIN_SIZE = 20;

SwitchBox::SwitchBox()
{
}


SwitchBox::~SwitchBox()
{
}

void SwitchBox::setPosition(const int x, const int y)
{
	this->_x = x;
	this->_y = y;
}

int SwitchBox::x() const
{
	return this->_x;
}

int SwitchBox::y() const
{
	return this->_y;
}

/**
 * 设置布线盒的大小。
 * @param width 宽度。
 * @param height 高度。
 */
void SwitchBox::setSize(const int width, const int height)
{
	this->_width = width > 10 ? width : 10;
	this->_height = height > 10 ? height : 10;
}

/**
 * 返回布线盒的宽度。
 * @return 宽度。
 */
int SwitchBox::width() const
{
	return this->_width;
}

/**
 * 返回布线盒的高度。
 * @return 高度。
 */
int SwitchBox::height() const
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
		pin.setShift((int)(i * margin));
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
	margin = this->_height / (right + 1);
	for (int i = 1; i <= right; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_RIGHT);
		pin.setShift((int)(i * margin));
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
	margin = this->_width / (bottom + 1);
	for (int i = 0; i < bottom; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_BOTTOM);
		pin.setShift((int)((bottom - i) * margin));
		pin.setId(++id);
		this->_pin.push_back(pin);
	}
	margin = this->_height / (left + 1);
	for (int i = 0; i < left; ++i)
	{
		Pin pin;
		pin.setOrientation(Pin::ORI_LEFT);
		pin.setShift((int)((left - i) * margin));
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
		archive << this->_x << this->_y;
		archive << this->_width << this->_height;
		/*archive << this->_pin.size();
		for (unsigned int i = 0; i < this->_pin.size(); ++i)
		{
			this->_pin[i].serialize(archive);
		}
		archive << this->_wire.size();
		for (unsigned int i = 0; i < this->_wire.size(); ++i)
		{
			this->_wire[i].serialize(archive);
		}*/
	}
	else
	{
		unsigned int size;
		archive >> this->_x >> this->_y;
		archive >> this->_width >> this->_height;
		archive >> size;
		/*this->_pin.clear();
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
		}*/
	}
}

/**
 * 获取外部边界。
 * @return 边界。
 */
CRect SwitchBox::getOuterBorder() const
{
	return CRect(this->_x, this->_y, this->_x + this->_width, this->_y + this->_height);
}

/**
* 获取内部边界。
* @return 边界。
*/
CRect SwitchBox::getInnerBorder() const
{
	return CRect(this->_x + PADDING, this->_y + PADDING, this->_x + this->_width - PADDING, this->_y + this->_height - PADDING);
}

/**
 * 获取引脚的中心位置。
 * @param index 引脚下标。
 * @return 引脚中心位置。
 */
CPoint SwitchBox::getPinCenter(const int index) const
{
	int cx, cy;
	switch (this->_pin[index].orientation())
	{
	case Pin::ORI_TOP:
		cx = this->_x + this->_pin[index].shift();
		cy = this->_y - (PIN_SIZE >> 1) + 1;
		break;
	case Pin::ORI_BOTTOM:
		cx = this->_x + this->_pin[index].shift();
		cy = this->_y + this->_height + (PIN_SIZE >> 1) - 1;
		break;
	case Pin::ORI_LEFT:
		cx = this->_x - (PIN_SIZE >> 1) + 1;
		cy = this->_y + this->_pin[index].shift();
		break;
	case Pin::ORI_RIGHT:
		cx = this->_x + this->_width + (PIN_SIZE >> 1) - 1;
		cy = this->_y + this->_pin[index].shift();
		break;
	}
	return CPoint(cx, cy);
}

/**
* 获取内部端口的中心位置。
* @param index 引脚下标。
* @return 内部端口中心位置。
*/
CPoint SwitchBox::getPortCenter(const int index) const
{
	int px, py;
	switch (this->_pin[index].orientation())
	{
	case Pin::ORI_TOP:
		px = this->_x + this->_pin[index].shift();
		py = this->_y + (PADDING << 1);
		break;
	case Pin::ORI_BOTTOM:
		px = this->_x + this->_pin[index].shift();
		py = this->_y + this->_height - (PADDING << 1);
		break;
	case Pin::ORI_LEFT:
		px = this->_x + (PADDING << 1);
		py = this->_y + this->_pin[index].shift();
		break;
	case Pin::ORI_RIGHT:
		px = this->_x + this->_width - (PADDING << 1);
		py = this->_y + this->_pin[index].shift();
		break;
	}
	return CPoint(px, py);
}

/**
* 获取引脚的矩形位置。
* @param index 引脚下标。
* @return 引脚矩形位置。
*/
CRect SwitchBox::getPinRect(const int index) const
{
	CPoint center = this->getPinCenter(index);
	return CRect(center.x - (PIN_SIZE >> 1), center.y - (PIN_SIZE >> 1), center.x + (PIN_SIZE >> 1), center.y + (PIN_SIZE >> 1));
}

/**
* 获取引脚文字的绘制位置。
* @param index 引脚下标。
* @return 引脚文字的绘制位置。
*/
CRect SwitchBox::getPinTextRect(const int index) const
{
	CPoint center = this->getPinCenter(index);
	return CRect(center.x - 1000, center.y - 1000, center.x + 1000, center.y + 1000);
}

/**
* 获取内部端口的矩形位置。
* @param index 引脚下标。
* @return 内部端口的矩形位置。
*/
CRect SwitchBox::getPortRect(const int index) const
{
	CPoint center = this->getPortCenter(index);
	return CRect(center.x - PADDING, center.y - PADDING, center.x + PADDING, center.y + PADDING);
}