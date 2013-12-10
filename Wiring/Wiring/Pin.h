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
	void setShift(const int shift);
	int shift() const;
	void serialize(CArchive &archive);
	void setId(const int id);
	int id() const;

private:
	Orientation _orientation;
	int _shift;
	int _id;
};

