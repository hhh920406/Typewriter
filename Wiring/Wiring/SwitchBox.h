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
	void setTitle(const CStringW &title);
	CStringW title() const;
	void setSize(const double width, const double height);
	double width() const;
	double height() const;
	std::vector<Pin>& pin();
	std::vector<Wire>& wire();
	void serialize(CArchive &archive);

private:
	CStringW _title;
	double _width;
	double _height;
	std::vector<Pin> _pin;
	std::vector<Wire> _wire;
};

