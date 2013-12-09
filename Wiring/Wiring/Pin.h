#pragma once
#include "Wire.h"

/**
 * �������ŵķ�װ���������ŵ�λ����Ϣ��
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
	 * ���캯����Ĭ�����������Ͻǡ�
	 */
	Pin();
	virtual ~Pin();
	/**
	 * �������ŵķ�λ��
	 * @param orientation ���ŵķ�λ��
	 */
	void setOrientation(const Orientation orientation);
	/**
	 * �������ŵķ�λ��
	 * @return orientation ���ŵķ�λ��
	 */
	Orientation orientation() const;
	/**
	 * �������ŵ�ƫ������
	 * ������������·�λ����ƫ����Ϊ�����оƬ��˵ľ��롣
	 * ������������ҷ�λ����ƫ����Ϊ�����оƬ�϶˵ľ��롣
	 * @param shift ƫ������
	 */
	void setShift(const double shift);
	/**
	 * �������ŵ�ƫ������
	 * @see setShift
	 * @return ƫ������
	 */
	double shift() const;
	/**
	 * ���л���
	 * @param archive �鵵����
	 */
	void Serialize(CArchive &archive);

private:
	Orientation _orientation; /** ���ŵķ�λ�� */
	double _shift; /** ���ŵ�ƫ������ */
};

