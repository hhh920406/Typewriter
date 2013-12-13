/**
 * 开关布线盒，使用Pin和Wire保存相关信息。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "Pin.h"
#include "Wire.h"

class SwitchBox
{
public:
	SwitchBox();
	virtual ~SwitchBox();
	void setPosition(const int x, const int y);
	int x() const;
	int y() const;
	void setSize(const int width, const int height);
	int width() const;
	int height() const;
	int left() const;
	int right() const;
	int top() const;
	int bottom() const;
	void setPinNum(const int pinNum);
	int addPin();
	void removePin(const int index);
	std::vector<Pin>& pin();
	std::vector<Wire>& wire();
	void setWire(std::vector<Wire> &wire);
	void addWire(const int u, const int v);
	void serialize(CArchive &archive);
	CRect getOuterBorder() const;
	CRect getInnerBorder() const;
	CRect getLeaveRect() const;
	CRect getPinBorder() const;
	CPoint getPinCenter(const int index) const;
	CPoint getPortCenter(const int index) const;
	CRect getPinRect(const int index) const;
	CRect getPinTextRect(const int index) const;
	CRect getPortRect(const int index) const;
	bool isOnBorder(const CPoint &pos) const;
	bool isOnLeftBorder(const CPoint &pos) const;
	bool isOnRightBorder(const CPoint &pos) const;
	bool isOnTopBorder(const CPoint &pos) const;
	bool isOnBottomBorder(const CPoint &pos) const;
	bool isOnInner(const CPoint &pos) const;
	bool isOnPaint(const CPoint &pos) const;
	bool isLeaveArea(const CPoint &pos) const;
	int pinHoverIndex(const CPoint &pos) const;
	int portHoverIndex(const CPoint &pos) const;

private:
	int _x;
	int _y;
	int _width;
	int _height;
	std::vector<Pin> _pin;
	std::vector<Wire> _wire;

	bool isInside(const CPoint &pos, const CRect &rect) const;
};

