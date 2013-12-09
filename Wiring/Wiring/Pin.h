#pragma once
#include "Wire.h"

/**
 * 对于引脚的封装，保存引脚的位置信息。
 * @author ZHG <CyberZHG@gmail.com>
 */

class Pin
{
public:
	enum Orientation
	{
		ORI_TOP,
		ORI_BOTTOM,
		ORI_LEFT,
		ORI_RIGHT
	};
	Pin();
	virtual ~Pin();
	void setOrientation(const Orientation orientation);
	Orientation orientation() const;
	void setShift(const double shift);
	double shift() const;
	void serialize(CArchive &archive);

private:
	Orientation _orientation;
	double _shift;
};

