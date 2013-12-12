#include "stdafx.h"
#include "SwitchBoxSolver.h"
using namespace std;

SwitchBoxSolver::SwitchBoxSolver()
{
}


SwitchBoxSolver::~SwitchBoxSolver()
{
}

/**
 * �Բ����������̰����⡣
 * ÿ�����Ӿ������������Ҫ���ӵĶ˿ڡ�
 * @param box Ҫ���ߵĲ��ߺС�
 * @return �Ͳ��ߺ�˳��һ����Ӧ�Ĳ��ߵ��������������������С�ڲ��ߺе�������˵������ʧ�ܡ�
 */
vector<Wire> SwitchBoxSolver::getGreedySolution(SwitchBox &box)
{

}

/** 
 * �Ż����ߺе���⡣
 * @param box �Ѿ��ɹ��õ�̰�Ľ�Ĳ��ߺС�
 * @return һ���Ż��Ĳ��ߣ�ÿһ�����߶���һ���Ż���
 */
vector<Wire> SwitchBoxSolver::optimizeSolution(SwitchBox &box)
{

}

/**
 * �Բ��ߺ��ڲ�������ɢ����
 * @param box Ҫ���ߵĲ��ߺС�
 */
void SwitchBoxSolver::discreteSwitchBox(SwitchBox &box)
{

}

/**
 * ��ȡ���ŵ�λ�á�
 * @param box Ҫ���ߵĲ��ߺС�
 */
void SwitchBoxSolver::getPinPosition(SwitchBox &box)
{
	this->_pinPosition.clear();
	for (unsigned i = 0; i < box.pin().size(); ++i)
	{
		switch (box.pin()[i].orientation)
		{
		case Pin::ORI_TOP:
			this->_pinPosition.push_back(box.pin()[i].shift());
			break;
		case Pin::ORI_RIGHT:
			this->_pinPosition.push_back(box.pin()[i].shift() + box.width());
			break;
		case Pin::ORI_BOTTOM:
			this->_pinPosition.push_back(- box.pin()[i].shift() + (box.width() << 1) + box.height());
			break;
		case Pin::ORI_LEFT:
			this->_pinPosition.push_back(-box.pin()[i].shift() + (box.width() << 1) + (box.height() << 1));
			break;
		}
	}
}