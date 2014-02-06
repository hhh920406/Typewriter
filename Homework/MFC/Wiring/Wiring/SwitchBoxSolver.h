/**
 * 用于求解布线盒的布线问题。
 * @author ZHG <CyberZHG@gmail.com>
 */
#pragma once
#include <vector>
#include <queue>
#include "SwitchBox.h"

class SwitchBoxSolver
{
public:
    SwitchBoxSolver();
    virtual ~SwitchBoxSolver();
    
    std::vector<Wire> getGreedySolution(SwitchBox &box);
    int getElapsedTime() const;

private:
    void getPinPosition(SwitchBox &box);
    void initGraph(SwitchBox &box);
    int getPinDist(int u, int v) const;
    int getPinPosition(int id) const;
    Wire getGreedySolution(SwitchBox &box, int u, int v);
    CPoint getPinGraphPosition(SwitchBox &box, int id);
    long long getStatus(int x, int y, int dir);
    int getStatusX(long long status);
    int getStatusY(long long status);
    int getStatusDir(long long status);
    CPoint getOriginPosition(int x, int y);
    int getStartOrientation(SwitchBox &box, int id);

    int _time;

    std::vector<int> _pinPosition;
    std::vector<bool> _dealt;

    int _row;
    int _col;
    std::vector< std::vector<bool> > _graph;
    std::vector< std::vector< std::vector<long long> > > _dist;
    std::vector< std::vector< std::vector<long long> > > _prev;
    std::vector< std::vector< std::vector<bool> > > _visit;
    std::queue<long long> _queue;
};

