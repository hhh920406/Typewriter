/**
 * ���ز��ߺУ�ʹ��Pin��Wire���������Ϣ��
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
	void setPinNum(const int pinNum);
	std::vector<Pin>& pin();
	std::vector<Wire>& wire();
	void serialize(CArchive &archive);
	CRect getOuterBorder() const;
	CRect getInnerBorder() const;
	CPoint getPinCenter(const int index) const;
	CPoint getPortCenter(const int index) const;
	CRect getPinRect(const int index) const;
	CRect getPinTextRect(const int index) const;
	CRect getPortRect(const int index) const;

private:
	int _x;
	int _y;
	int _width;
	int _height;
	std::vector<Pin> _pin;
	std::vector<Wire> _wire;
};

