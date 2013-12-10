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
void Pin::setShift(const int shift)
{
	this->_shift = shift;
}

/**
 * �������ŵ�ƫ������
 * @see setShift
 * @return ƫ������
 */
int Pin::shift() const
{
	return this->_shift;
}

/**
 * ���л���
 * @param archive �鵵����
 */
void Pin::serialize(CArchive &archive)
{
	if (archive.IsStoring())
	{
		int orientation = this->_orientation;
		archive << orientation << this->_shift;
	}
	else
	{
		int orientation;
		archive >> orientation >> this->_shift;
		this->_orientation = Orientation(orientation);
	}
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