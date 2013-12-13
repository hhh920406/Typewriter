/**
 * �������ŵķ�װ���������ŵ�λ����Ϣ��
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include "Wire.h"

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
	void setId(const int id);
	int id() const;
	friend bool operator <(const Pin &a, const Pin &b);

private:
	Orientation _orientation;
	double _shift;
	int _id;
};

