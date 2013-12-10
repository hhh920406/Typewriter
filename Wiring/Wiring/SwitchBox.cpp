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
	int nextWidth = width > 10 ? width : 10;
	int nextHeight = height > 10 ? height : 10;
	for (unsigned int i = 0; i < this->_pin.size(); ++i)
	{
		switch (this->_pin[i].orientation())
		{
		case Pin::ORI_TOP:
		case Pin::ORI_BOTTOM:
			this->_pin[i].setShift(this->_pin[i].shift() * nextWidth / this->_width);
			break;
		case Pin::ORI_LEFT:
		case Pin::ORI_RIGHT:
			this->_pin[i].setShift(this->_pin[i].shift() * nextHeight / this->_height);
			break;
		}
	}
	for (unsigned int i = 0; i < this->_wire.size(); ++i)
	{
		for (int j = 0; j < this->_wire[i].count(); ++j)
		{
			this->_wire[i].set(j, this->_wire[i].x(j) * nextWidth / this->_width, this->_wire[i].y(j) * nextHeight / this->_height);
		}
	}
	this->_width = nextWidth;
	this->_height = nextHeight;
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
 * 返回左边界位置。
 * @return 左边界位置。
 */
int SwitchBox::left() const
{
	return this->_x;
}

/**
 * 返回右边界位置。
 * @return 右边界位置。
 */
int SwitchBox::right() const
{
	return this->_x + this->_width;
}

/**
 * 返回上边界位置。
 * @return 上边界位置。
 */
int SwitchBox::top() const
{
	return this->_y;
}

/**
 * 返回下边界位置。
 * @return 下边界位置。
 */
int SwitchBox::bottom() const
{
	return this->_y + this->_height;
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
 * 添加一个初始布线。
 * @param u 端口1。
 * @param v 端口2。
 */
void SwitchBox::addWire(const int u, const int v)
{
	for (int i = this->_wire.size() - 1; i >= 0; --i)
	{
		if (this->_wire[i].u() == u || this->_wire[i].u() == v || this->_wire[i].v() == u || this->_wire[i].v() == v)
		{
			this->_wire.erase(this->_wire.begin() + i);
		}
	}
	Wire wire;
	wire.setU(u);
	wire.setV(v);
	wire.add(this->getPortCenter(u).x - this->_x, this->getPortCenter(u).y - this->_y);
	wire.add(this->getPortCenter(v).x - this->_x, this->getPortCenter(v).y - this->_y);
	this->_wire.push_back(wire);
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
 * 获取包含引脚在内的边界。
 * @return 边界。
 */
CRect SwitchBox::getPinBorder() const
{
	return CRect(this->_x - PIN_SIZE, this->_y - PIN_SIZE, this->_x + this->_width + PIN_SIZE, this->_y + this->_height + PIN_SIZE);
}

/**
 * 获取引脚的中心位置。
 * @param index 引脚下标。
 * @return 引脚中心位置。
 */
CPoint SwitchBox::getPinCenter(const int index) const
{
	double cx, cy;
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
	return CPoint((int)cx, (int)cy);
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

/**
 * 判断当前点是否在布线盒的边界上。
 * @param pos 要查询的位置。
 * @return 如果在边界上返回true，否则返回false。
 */
bool SwitchBox::isOnBorder(const CPoint &pos) const
{
	return this->isInside(pos, this->getOuterBorder()) && !this->isInside(pos, this->getInnerBorder());
}

/**
 * 判断当前点是否在左边界上。
 * @param pos 要查询的位置。
 * @return 如果在边界上返回true，否则返回false。
 */
bool SwitchBox::isOnLeftBorder(const CPoint &pos) const
{
	return this->isOnBorder(pos) && pos.x <= this->_x + PADDING;
}

/**
 * 判断当前点是否在右边界上。
 * @param pos 要查询的位置。
 * @return 如果在边界上返回true，否则返回false。
 */
bool SwitchBox::isOnRightBorder(const CPoint &pos) const
{
	return this->isOnBorder(pos) && pos.x >= this->_x + this->_width - PADDING;
}

/**
 * 判断当前点是否在上边界上。
 * @param pos 要查询的位置。
 * @return 如果在边界上返回true，否则返回false。
 */
bool SwitchBox::isOnTopBorder(const CPoint &pos) const
{
	return this->isOnBorder(pos) && pos.y <= this->_y + PADDING;
}

/**
 * 判断当前点是否在下边界上。
 * @param pos 要查询的位置。
 * @return 如果在边界上返回true，否则返回false。
 */
bool SwitchBox::isOnBottomBorder(const CPoint &pos) const
{
	return this->isOnBorder(pos) && pos.y >= this->_y + this->_height - PADDING;
}

bool SwitchBox::isOnInner(const CPoint &pos) const
{
	return this->isInside(pos, this->getInnerBorder());
}

/**
 * 判断当前点指向哪个引脚。
 * @param pos 要查询的位置。
 * @return 如果在引脚上则返回引脚的下标，否则返回-1。
 */
int SwitchBox::pinHoverIndex(const CPoint &pos) const
{
	for (unsigned int i = 0; i < this->_pin.size(); ++i)
	{
		if (this->isInside(pos, this->getPinRect(i)))
		{
			return i;
		}
	}
	return -1;
}

/**
 * 判断当前点指向哪个端口。
 * @param pos 要查询的位置。
 * @return 如果在端口上则返回引脚的下标，否则返回-1。
 */
int SwitchBox::portHoverIndex(const CPoint &pos) const
{
	for (unsigned int i = 0; i < this->_pin.size(); ++i)
	{
		if (this->isInside(pos, this->getPortRect(i)))
		{
			return i;
		}
	}
	return -1;
}

/**
 * 判断点是否在矩形中。
 * @param pos 要判断的点。
 * @param rect 要判断的矩形。
 * @return 如果在矩形中返回true，否则返回false。
 */
bool SwitchBox::isInside(const CPoint &pos, const CRect &rect) const
{
	return pos.x >= rect.left && pos.x <= rect.right && pos.y >= rect.top && pos.y <= rect.bottom;
}