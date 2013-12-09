#pragma once
#include "Pin.h"
#include "Wire.h"

/**
 * ���ز��ߺУ�ʹ��Pin��Wire���������Ϣ��
 * @author ZHG <CyberZHG@gmail.com>
 */

class SwitchBox
{
public:
	SwitchBox();
	virtual ~SwitchBox();
	/**
	 * ���ò��ߺеı��⡣
	 * @param title ���⡣
	 */
	void setTitle(const CStringW &title);
	/**
	 * ���ز��ߺеı��⡣
	 * @return ���⡣
	 */
	CStringW title() const;
	/**
	 * ���ò��ߺеĴ�С��
	 * @param width ��ȡ�
	 * @param height �߶ȡ�
	 */
	void setSize(const double width, const double height);
	/**
	 * ���ز��ߺеĿ�ȡ�
	 * @return ��ȡ�
	 */
	double width() const;
	/**
	 * ���ز��ߺеĸ߶ȡ�
	 * @return �߶ȡ�
	 */
	double height() const;
	/**
	 * �������ŵ�������
	 * @return ���š�
	 */
	std::vector<Pin>& pin();
	/**
	* �������ߵ�������
	* @return ���ߡ�
	*/
	std::vector<Wire>& wire();
	/**
	* ���л���
	* @param archive �鵵����
	*/
	void serialize(CArchive &archive);

private:
	CStringW _title;
	double _width;
	double _height;
	std::vector<Pin> _pin;
	std::vector<Wire> _wire;
};

