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
 * 对布线问题进行贪心求解。
 * 每次连接距离最近两个需要连接的端口。
 * @param box 要布线的布线盒。
 * @return 和布线盒顺序不一定对应的布线的向量，如果向量的数量小于布线盒的数量则说明布线失败。
 */
vector<Wire> SwitchBoxSolver::getGreedySolution(SwitchBox &box)
{

}

/** 
 * 优化布线盒的求解。
 * @param box 已经成功得到贪心解的布线盒。
 * @return 一组优化的布线，每一个布线都是一次优化。
 */
vector<Wire> SwitchBoxSolver::optimizeSolution(SwitchBox &box)
{

}

/**
 * 对布线盒内部进行离散化。
 * @param box 要布线的布线盒。
 */
void SwitchBoxSolver::discreteSwitchBox(SwitchBox &box)
{

}

/**
 * 获取引脚的位置。
 * @param box 要布线的布线盒。
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