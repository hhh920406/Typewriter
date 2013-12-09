#pragma once
#include <vector>

/**
 * 连接两个引脚的连线的结构，由一组有顺序的坐标表示。
 * @author ZHG <CyberZHG@gmail.com>
 */

class Wire
{
public:
	/**
	 * 构造函数。默认的节点数为0。
	 */
	Wire();
	virtual ~Wire();
	/**
	 * 为连线添加新的节点。
	 * @param x 新节点的横坐标。
	 * @param y 新节点的纵坐标。
	 */
	void add(const double x, const double y);
	/**
	 * 移除指定位置的节点。
	 * @param index 要移除的节点的下标，如果不合法则不进行操作。
	 */
	void remove(int index);
	/**
	 * 获取节点的数目。
	 * @return 节点的数目。
	 */
	int count() const;
	/**
	 * 设置指点位置的节点的坐标。
	 * @param index 要变更的节点的下标。
	 * @param x 新的横坐标。
	 * @param y 新的纵坐标。
	 */
	void set(const int index, const double x, const double y);
	/**
	 * 获取横坐标。
	 * @param 要获取的节点的下标。
	 * @return 横坐标。
	 */
	double x(const int index) const;
	/**
	* 获取纵坐标。
	* @param 要获取的节点的下标。
	* @return 纵坐标。
	*/
	double y(const int index) const;

private:
	std::vector<double> _x; /** 横坐标的向量。 */
	std::vector<double> _y; /** 纵坐标的向量。 */
};

