/**
 * 连接两个引脚的连线的结构，由一组有顺序的坐标表示。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include <vector>

class Wire
{
public:
	Wire();
	virtual ~Wire();
	void add(const double x, const double y);
	void remove(unsigned int index);
	int count() const;
	void set(const unsigned int index, const double x, const double y);
	double x(const unsigned int index) const;
	double y(const unsigned int index) const;
	void setU(const unsigned int u);
	void setV(const unsigned int v);
	unsigned int u() const;
	unsigned int v() const;
	void serialize(CArchive &archive);

private:
	std::vector<double> _x;
	std::vector<double> _y;
	unsigned int _u;
	unsigned int _v;
};

