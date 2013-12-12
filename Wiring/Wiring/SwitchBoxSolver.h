/**
 * 用于求解布线盒的布线问题。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include <vector>
#include "SwitchBox.h"

class SwitchBoxSolver
{
public:
	SwitchBoxSolver();
	virtual ~SwitchBoxSolver();
	
	std::vector<Wire> getGreedySolution(SwitchBox &box);
	std::vector<Wire> optimizeSolution(SwitchBox &box);

private:
	void discreteSwitchBox(SwitchBox &box);
	void getPinPosition(SwitchBox &box);

	std::vector<double> _pinPosition;
};

