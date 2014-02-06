#include "stdafx.h"
#include "SwitchBox.h"
using namespace std;

const int PADDING = 3;
const int PIN_SIZE = 20;
const int LEAVE = 50;

SwitchBox::SwitchBox()
{
}

SwitchBox::~SwitchBox()
{
}

void SwitchBox::setName(const CStringW &name)
{
    this->_name = name;
}

CStringW SwitchBox::name() const
{
    return this->_name;
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
 * ���ò��ߺеĴ�С��
 * @param width ��ȡ�
 * @param height �߶ȡ�
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
 * ���ز��ߺеĿ�ȡ�
 * @return ��ȡ�
 */
int SwitchBox::width() const
{
    return this->_width;
}

/**
 * ���ز��ߺеĸ߶ȡ�
 * @return �߶ȡ�
 */
int SwitchBox::height() const
{
    return this->_height;
}

/**
 * ������߽�λ�á�
 * @return ��߽�λ�á�
 */
int SwitchBox::left() const
{
    return this->_x;
}

/**
 * �����ұ߽�λ�á�
 * @return �ұ߽�λ�á�
 */
int SwitchBox::right() const
{
    return this->_x + this->_width;
}

/**
 * �����ϱ߽�λ�á�
 * @return �ϱ߽�λ�á�
 */
int SwitchBox::top() const
{
    return this->_y;
}

/**
 * �����±߽�λ�á�
 * @return �±߽�λ�á�
 */
int SwitchBox::bottom() const
{
    return this->_y + this->_height;
}

/**
 * �������ŵ�������
 * @return ���š�
 */
vector<Pin>& SwitchBox::pin()
{
    return this->_pin;
}

/**
 * �������ߵ�������
 * @return ���ߡ�
 */
vector<Wire>& SwitchBox::wire()
{
    return this->_wire;
}

/**
 * �������ߡ�
 * @param wire ���ߡ�
 */
void SwitchBox::setWire(std::vector<Wire> &wire)
{
    this->_wire = wire;
}

/**
 * ���һ����ʼ���ߡ�
 * @param u �˿�1��
 * @param v �˿�2��
 */
void SwitchBox::addWire(const int u, const int v)
{
    int uid = this->_pin[u].id();
    int vid = this->_pin[v].id();
    for (int i = this->_wire.size() - 1; i >= 0; --i)
    {
        if (this->_wire[i].u() == uid || this->_wire[i].u() == vid || this->_wire[i].v() == uid || this->_wire[i].v() == vid)
        {
            this->_wire.erase(this->_wire.begin() + i);
        }
    }
    Wire wire;
    wire.setU(uid);
    wire.setV(vid);
    wire.add(this->getPortCenter(u).x - this->_x, this->getPortCenter(u).y - this->_y);
    wire.add(this->getPortCenter(v).x - this->_x, this->getPortCenter(v).y - this->_y);
    this->_wire.push_back(wire);
}

/**
 * �������ŵ�������Χ�Ʋ��ߺо��ȷֲ���
 * @param pinNum ���ŵ�������
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
 * ���һ�����š�
 * @return ���ػ�δ���ֹ�����С�����ű�š�
 */
int SwitchBox::addPin()
{
    for (int id = 1;; ++id)
    {
        bool flag = true;
        for (unsigned int i = 0; i < this->_pin.size(); ++i)
        {
            if (this->_pin[i].id() == id)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            Pin pin;
            pin.setId(id);
            this->_pin.push_back(pin);
            return this->_pin.size() - 1;
        }
    }
}

/**
 * ɾ��һ�����ţ���Ӧ������Ҳ�ᱻɾ����
 * @param index ���ŵ��±ꡣ
 */
void SwitchBox::removePin(const int index)
{
    int id = this->_pin[index].id();
    for (vector<Wire>::iterator it = this->_wire.begin(); it != this->_wire.end(); ++it)
    {
        if (it->u() == id || it->v() == id)
        {
            this->_wire.erase(it);
            break;
        }
    }
    this->_pin.erase(this->_pin.begin() + index);
}

/**
 * ��ȡ�ⲿ�߽硣
 * @return �߽硣
 */
CRect SwitchBox::getOuterBorder() const
{
    return CRect(this->_x, this->_y, this->_x + this->_width, this->_y + this->_height);
}

/**
* ��ȡ�ڲ��߽硣
* @return �߽硣
*/
CRect SwitchBox::getInnerBorder() const
{
    return CRect(this->_x + PADDING, this->_y + PADDING, this->_x + this->_width - PADDING, this->_y + this->_height - PADDING);
}

/**
 * ��ȡ�����������ڵı߽硣
 * @return �߽硣
 */
CRect SwitchBox::getPinBorder() const
{
    return CRect(this->_x - PIN_SIZE, this->_y - PIN_SIZE, this->_x + this->_width + PIN_SIZE, this->_y + this->_height + PIN_SIZE);
}

/**
 * ��ȡ���ŵ�����λ�á�
 * @param index �����±ꡣ
 * @return ��������λ�á�
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
 * ��ȡ�ڲ��˿ڵ�����λ�á�
 * @param index �����±ꡣ
 * @return �ڲ��˿�����λ�á�
 */
CPoint SwitchBox::getPortCenter(const int index) const
{
    double px, py;
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
    return CPoint((int)px, (int)py);
}

/**
 * ��ȡ���ŵľ���λ�á�
 * @param index �����±ꡣ
 * @return ���ž���λ�á�
 */
CRect SwitchBox::getPinRect(const int index) const
{
    CPoint center = this->getPinCenter(index);
    return CRect(center.x - (PIN_SIZE >> 1), center.y - (PIN_SIZE >> 1), center.x + (PIN_SIZE >> 1), center.y + (PIN_SIZE >> 1));
}

/**
 * ��ȡ�������ֵĻ���λ�á�
 * @param index �����±ꡣ
 * @return �������ֵĻ���λ�á�
 */
CRect SwitchBox::getPinTextRect(const int index) const
{
    CPoint center = this->getPinCenter(index);
    return CRect(center.x - 1000, center.y - 1000, center.x + 1000, center.y + 1000);
}

/**
 * ��ȡ�ڲ��˿ڵľ���λ�á�
 * @param index �����±ꡣ
 * @return �ڲ��˿ڵľ���λ�á�
 */
CRect SwitchBox::getPortRect(const int index) const
{
    CPoint center = this->getPortCenter(index);
    return CRect(center.x - PADDING, center.y - PADDING, center.x + PADDING, center.y + PADDING);
}

/**
* ��ȡ�뿪����ľ���λ�á�
* @return �뿪����ľ���λ�á�
*/
CRect SwitchBox::getLeaveRect() const
{
    return CRect(this->left() - LEAVE, this->top() - LEAVE, this->right() + LEAVE, this->bottom() + LEAVE);
}

/**
 * �жϵ�ǰ���Ƿ��ڲ��ߺеı߽��ϡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ����ڱ߽��Ϸ���true�����򷵻�false��
 */
bool SwitchBox::isOnBorder(const CPoint &pos) const
{
    return this->isInside(pos, this->getOuterBorder()) && !this->isInside(pos, this->getInnerBorder());
}

/**
 * �жϵ�ǰ���Ƿ�����߽��ϡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ����ڱ߽��Ϸ���true�����򷵻�false��
 */
bool SwitchBox::isOnLeftBorder(const CPoint &pos) const
{
    return this->isOnBorder(pos) && pos.x <= this->_x + PADDING;
}

/**
 * �жϵ�ǰ���Ƿ����ұ߽��ϡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ����ڱ߽��Ϸ���true�����򷵻�false��
 */
bool SwitchBox::isOnRightBorder(const CPoint &pos) const
{
    return this->isOnBorder(pos) && pos.x >= this->_x + this->_width - PADDING;
}

/**
 * �жϵ�ǰ���Ƿ����ϱ߽��ϡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ����ڱ߽��Ϸ���true�����򷵻�false��
 */
bool SwitchBox::isOnTopBorder(const CPoint &pos) const
{
    return this->isOnBorder(pos) && pos.y <= this->_y + PADDING;
}

/**
 * �жϵ�ǰ���Ƿ����±߽��ϡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ����ڱ߽��Ϸ���true�����򷵻�false��
 */
bool SwitchBox::isOnBottomBorder(const CPoint &pos) const
{
    return this->isOnBorder(pos) && pos.y >= this->_y + this->_height - PADDING;
}

/**
 * �жϵ�ǰ���Ƿ��ڲ��ߺ��ڲ���
 * @param pos Ҫ��ѯ��λ�á�
 * @return ������ڲ�����true�����򷵻�false��
 */
bool SwitchBox::isOnInner(const CPoint &pos) const
{
    return this->isInside(pos, this->getInnerBorder());
}

/**
 * �жϵ�ǰ���Ƿ����л��Ƶ������ڡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ������ڲ�����true�����򷵻�false��
 */
bool SwitchBox::isOnPaint(const CPoint &pos) const
{
    return this->isInside(pos, this->getPinBorder());
}

/**
 * �Ƿ�Զ��Ļ�������
 * @param pos Ҫ��ѯ��λ�á�
 * @return ���Զ�뷵��true�����򷵻�false��
 */
bool SwitchBox::isLeaveArea(const CPoint &pos) const
{
    return !this->isInside(pos, this->getLeaveRect());
}

/**
 * �жϵ�ǰ��ָ���ĸ����š�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ������������򷵻����ŵ��±꣬���򷵻�-1��
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
 * �жϵ�ǰ��ָ���ĸ��˿ڡ�
 * @param pos Ҫ��ѯ��λ�á�
 * @return ����ڶ˿����򷵻����ŵ��±꣬���򷵻�-1��
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
 * �жϵ��Ƿ��ھ����С�
 * @param pos Ҫ�жϵĵ㡣
 * @param rect Ҫ�жϵľ��Ρ�
 * @return ����ھ����з���true�����򷵻�false��
 */
bool SwitchBox::isInside(const CPoint &pos, const CRect &rect) const
{
    return pos.x >= rect.left && pos.x <= rect.right && pos.y >= rect.top && pos.y <= rect.bottom;
}