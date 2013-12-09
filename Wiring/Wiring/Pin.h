#pragma once
#include "Wire.h"

/**
 * 对于引脚的封装，保存引脚的位置信息。
 * @author ZHG <CyberZHG@gmail.com>
 */

class Pin : public CObject
{
public:
	enum Orientation
	{
		ORI_TOP,
		ORI_BOTTOM,
		ORI_LEFT,
		ORI_RIGHT
	};
	/**
	 * 构造函数。默认引脚在左上角。
	 */
	Pin();
	virtual ~Pin();
	/**
	 * 设置引脚的方位。
	 * @param orientation 引脚的方位。
	 */
	void setOrientation(const Orientation orientation);
	/**
	 * 返回引脚的方位。
	 * @return orientation 引脚的方位。
	 */
	Orientation orientation() const;
	/**
	 * 设置引脚的偏移量。
	 * 如果引脚在上下方位，则偏移量为横向距芯片左端的距离。
	 * 如果引脚在左右方位，则偏移量为纵向距芯片上端的距离。
	 * @param shift 偏移量。
	 */
	void setShift(const double shift);
	/**
	 * 返回引脚的偏移量。
	 * @see setShift
	 * @return 偏移量。
	 */
	double shift() const;
	/**
	 * 序列化。
	 * @param archive 归档对象。
	 */
	void Serialize(CArchive &archive);

private:
	Orientation _orientation; /** 引脚的方位。 */
	double _shift; /** 引脚的偏移量。 */
};

