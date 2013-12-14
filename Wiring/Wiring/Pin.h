/**
 * 对于引脚的封装，保存引脚的位置信息。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "Wire.h"

class Pin
{
public:
	enum Orientation
	{
		ORI_TOP = 0,
		ORI_RIGHT = 1,
		ORI_BOTTOM = 2,
		ORI_LEFT = 3
	};
	Pin();
	virtual ~Pin();
	void setOrientation(const Orientation orientation);
	Orientation orientation() const;
	void setShift(const double shift);
	double shift() const;
	void setId(const int id);
	int id() const;
	friend bool operator <(const Pin &a, const Pin &b);

private:
	Orientation _orientation;
	double _shift;
	int _id;
};

