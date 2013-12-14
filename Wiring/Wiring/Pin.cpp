#include "stdafx.h"
#include "Pin.h"

/**
 * ���캯����Ĭ�����������Ͻǡ�
 */
Pin::Pin()
{
	this->setOrientation(ORI_TOP);
	this->setShift(0.0);
}


Pin::~Pin()
{
}

/**
 * �������ŵķ�λ��
 * @param orientation ���ŵķ�λ��
 */
void Pin::setOrientation(const Orientation orientation)
{
	this->_orientation = orientation;
}

/**
 * �������ŵķ�λ��
 * @return orientation ���ŵķ�λ��
 */
Pin::Orientation Pin::orientation() const
{
	return this->_orientation;
}

/**
 * �������ŵ�ƫ������
 * ������������·�λ����ƫ����Ϊ�����оƬ��˵ľ��롣
 * ������������ҷ�λ����ƫ����Ϊ�����оƬ�϶˵ľ��롣
 * @param shift ƫ������
 */
void Pin::setShift(const double shift)
{
	this->_shift = shift;
}

/**
 * �������ŵ�ƫ������
 * @see setShift
 * @return ƫ������
 */
double Pin::shift() const
{
	return this->_shift;
}

/**
 * �������ŵı�š�
 * @param id ��š�
 */
void Pin::setId(const int id)
{
	this->_id = id;
}

/**
 * ��ȡ���ŵı�š�
 * @return ��š�
 */
int Pin::id() const
{
	return this->_id;
}

/**
 * ��Բ�ܶ����Ž�������
 * @param a ����1��
 * @param b ����2��
 * @return ���������ǰ����true��
 */
bool operator <(const Pin &a, const Pin &b)
{
	if (a.orientation() == b.orientation())
	{
		if (a.orientation() == Pin::ORI_TOP || a.orientation() == Pin::ORI_RIGHT)
		{
			return a.shift() < b.shift();
		}
		else
		{
			return a.shift() > b.shift();
		}
	}
	return a.orientation() < b.orientation();
}