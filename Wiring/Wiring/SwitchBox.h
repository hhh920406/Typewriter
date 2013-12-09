#pragma once
#include "Pin.h"
#include "Wire.h"

/**
 * 开关布线盒，使用Pin和Wire保存相关信息。
 * @author ZHG <CyberZHG@gmail.com>
 */

class SwitchBox
{
public:
	SwitchBox();
	virtual ~SwitchBox();
	/**
	 * 设置布线盒的标题。
	 * @param title 标题。
	 */
	void setTitle(const CStringW &title);
	/**
	 * 返回布线盒的标题。
	 * @return 标题。
	 */
	CStringW title() const;
	/**
	 * 设置布线盒的大小。
	 * @param width 宽度。
	 * @param height 高度。
	 */
	void setSize(const double width, const double height);
	/**
	 * 返回布线盒的宽度。
	 * @return 宽度。
	 */
	double width() const;
	/**
	 * 返回布线盒的高度。
	 * @return 高度。
	 */
	double height() const;
	/**
	 * 返回引脚的向量。
	 * @return 引脚。
	 */
	std::vector<Pin>& pin();
	/**
	* 返回连线的向量。
	* @return 连线。
	*/
	std::vector<Wire>& wire();
	/**
	* 序列化。
	* @param archive 归档对象。
	*/
	void serialize(CArchive &archive);

private:
	CStringW _title;
	double _width;
	double _height;
	std::vector<Pin> _pin;
	std::vector<Wire> _wire;
};

