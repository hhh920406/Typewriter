#pragma once
#include <vector>

/**
 * �����������ŵ����ߵĽṹ����һ����˳��������ʾ��
 * @author ZHG <CyberZHG@gmail.com>
 */

class Wire
{
public:
	/**
	 * ���캯����Ĭ�ϵĽڵ���Ϊ0��
	 */
	Wire();
	virtual ~Wire();
	/**
	 * Ϊ��������µĽڵ㡣
	 * @param x �½ڵ�ĺ����ꡣ
	 * @param y �½ڵ�������ꡣ
	 */
	void add(const double x, const double y);
	/**
	 * �Ƴ�ָ��λ�õĽڵ㡣
	 * @param index Ҫ�Ƴ��Ľڵ���±꣬������Ϸ��򲻽��в�����
	 */
	void remove(int index);
	/**
	 * ��ȡ�ڵ����Ŀ��
	 * @return �ڵ����Ŀ��
	 */
	int count() const;
	/**
	 * ����ָ��λ�õĽڵ�����ꡣ
	 * @param index Ҫ����Ľڵ���±ꡣ
	 * @param x �µĺ����ꡣ
	 * @param y �µ������ꡣ
	 */
	void set(const int index, const double x, const double y);
	/**
	 * ��ȡ�����ꡣ
	 * @param Ҫ��ȡ�Ľڵ���±ꡣ
	 * @return �����ꡣ
	 */
	double x(const int index) const;
	/**
	* ��ȡ�����ꡣ
	* @param Ҫ��ȡ�Ľڵ���±ꡣ
	* @return �����ꡣ
	*/
	double y(const int index) const;

private:
	std::vector<double> _x; /** ������������� */
	std::vector<double> _y; /** ������������� */
};

