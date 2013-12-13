#include "stdafx.h"
#include <algorithm>
#include "SwitchBoxSolver.h"
using namespace std;
const long long INF = 0x3f3f3f3fLL;
const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
const int DIR_X[4] = { 1, 0, -1, 0 };
const int DIR_Y[4] = { 0, 1, 0, -1 };

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
	vector<Wire> greedyWire;
	this->getPinPosition(box);
	this->initGraph(box);
	vector<Wire>& wire = box.wire();
	vector<bool> solved(wire.size(), false);
	for (unsigned int i = 0; i < wire.size(); ++i)
	{
		int minDist = this->_pinPosition.size();
		int index = 0;
		for (unsigned int j = 0; j < wire.size(); ++j)
		{
			int dist = this->getPinDist(wire[j].u(), wire[j].v());
			if (dist < minDist)
			{
				minDist = dist;
				index = j;
			}
		}
		Wire singleWire = this->getGreedySolution(box, wire[index].u(), wire[index].v());
		if (singleWire.count() == 0)
		{
			return greedyWire;
		}
		greedyWire.push_back(singleWire);
	}
	return greedyWire;
}

/** 
 * �Ż����ߺе���⡣
 * @param box �Ѿ��ɹ��õ�̰�Ľ�Ĳ��ߺС�
 * @return һ���Ż��Ĳ��ߣ�ÿһ�����߶���һ���Ż���
 */
vector<Wire> SwitchBoxSolver::optimizeSolution(SwitchBox &box)
{
	vector<Wire> optWire;
	return optWire;
}

/**
 * ��ȡ���ŵ�λ�á�
 * @param box Ҫ���ߵĲ��ߺС�
 */
void SwitchBoxSolver::getPinPosition(SwitchBox &box)
{
	vector<Pin>& pin = box.pin();
	sort(pin.begin(), pin.end());
	this->_pinPosition.clear();
	this->_dealt.clear();
	for (unsigned int i = 0; i < pin.size(); ++i)
	{
		this->_pinPosition.push_back(pin[i].id());
		this->_dealt.push_back(true);
	}
	vector<Wire>& wire = box.wire();
	for (unsigned int i = 0; i < wire.size(); ++i)
	{
		int u = wire[i].u();
		int v = wire[i].v();
		for (unsigned int j = 0; j < pin.size(); ++i)
		{
			if (this->_pinPosition[j] == u)
			{
				this->_dealt[j] = false;
			}
			if (this->_pinPosition[j] == v)
			{
				this->_dealt[j] = false;
			}
		}
	}
}

/**
 * ��ʼ��ͼ�ṹ��
 * @param box Ҫ���ߵĲ��ߺС�
 */
void SwitchBoxSolver::initGraph(SwitchBox &box)
{
	for (unsigned int i = 0; i < this->_dist.size(); ++i)
	{
		for (unsigned int j = 0; j < this->_dist[i].size(); ++j)
		{
			this->_dist[i][j].clear();
			this->_prev[i][j].clear();
			this->_visit[i][j].clear();
		}
		this->_dist[i].clear();
		this->_prev[i].clear();
		this->_visit[i].clear();
		this->_graph[i].clear();
	}
	this->_dist.clear();
	this->_prev.clear();
	this->_visit.clear();
	this->_graph.clear();

	this->_row = (box.height() - 1) >> 1;
	this->_col = (box.width() - 1) >> 1;
	for (int i = 0; i < this->_row; ++i)
	{
		this->_graph.push_back(vector<bool>());
		this->_dist.push_back(vector< vector<long long> >());
		this->_prev.push_back(vector< vector<int> >());
		this->_visit.push_back(vector< vector<bool> >());
		for (int j = 0; j < this->_col; ++j)
		{
			this->_graph[i].push_back(false);
			this->_dist[i].push_back(vector<long long>(4));
			this->_prev[i].push_back(vector<int>(4));
			this->_visit[i].push_back(vector<bool>(4));
		}
	}
}

/**
 * ��ȡ�������ż�δ���ߵ����ŵ�������
 * @param u ���ű�š�
 * @param v ���ű�š�
 * @return ���ŵ������������Ų����ڷ���-1��
 */
int SwitchBoxSolver::getPinDist(int u, int v) const
{
	u = getPinPosition(u);
	v = getPinPosition(v);
	if (u == -1 || v == -1)
	{
		return -1;
	}
	int count1 = 0;
	for (int i = u + 1; i != v; ++i)
	{
		if (i >= this->_pinPosition.size())
		{
			i = 0;
		}
		count1 += this->_dealt[i];
	}
	int count2 = 0;
	for (int i = u - 1; i != v; --i)
	{
		if (i < 0)
		{
			i = this->_pinPosition.size() - 1;
		}
		count2 += this->_dealt[i];
	}
	return min(count1, count2);
}

/**
 * ��ȡ���ŵ��±ꡣ
 * @param id ���ű�š�
 * @return �����±꣬��������ڷ���-1��
 */
int SwitchBoxSolver::getPinPosition(int id) const
{
	for (unsigned int i = 0; i < this->_pinPosition.size(); ++i)
	{
		if (this->_pinPosition[i] == id)
		{
			return i;
		}
	}
	return -1;
}

/**
 * ��ȡһ�鲼�ߵ�̰�Ľ⡣
 * @param box Ҫ���ߵĲ��ߺС�
 * @param wire �ò��ߵ�������Ϣ��
 * @return �������ٵ�̰�Ľ⡣
 */
Wire SwitchBoxSolver::getGreedySolution(SwitchBox &box, int u, int v)
{
	CPoint start = this->getPinGraphPosition(box, u);
	CPoint end = this->getPinGraphPosition(box, v);
	for (unsigned int i = 0; i < this->_dist.size(); ++i)
	{
		for (unsigned int j = 0; j < this->_dist[i].size(); ++j)
		{
			for (unsigned int k = 0; k < this->_dist[i][j].size(); ++k)
			{
				this->_dist[i][j][k] = INFL;
				this->_prev[i][j][k] = -1;
				this->_visit[i][j][k] = false;
			}
		}
	}
	for (int k = 0; k < 4; ++k)
	{
		this->_dist[start.x][start.y][k] = 0;
		this->_visit[start.x][start.y][k] = true;
		this->_queue.push(this->getStatus(start.x, start.y, k));
	}
	while (!this->_queue.empty())
	{
		long long status = this->_queue.front();
		int x = this->getStatusX(status);
		int y = this->getStatusY(status);
		int dir = this->getStatusDir(status);
		for (int i = 0; i < 4; ++i)
		{
			int tx = x + DIR_X[i];
			int ty = y + DIR_Y[i];
			if (tx >= 0 && tx < this->_row)
			{
				if (ty >= 0 && ty < this->_col)
				{
					long long dist = this->_dist[x][y][dir] + 1;
					if (dir != i)
					{
						dist += INF;
					}
					if (dist < this->_dist[tx][ty][i])
					{
						this->_dist[tx][ty][i] = dist;
						this->_prev[tx][ty][u] = status;
						if (!this->_visit[tx][ty][i])
						{
							this->_visit[tx][ty][i] = true;
							this->_queue.push(this->getStatus(tx, ty, i));
						}
					}
				}
			}
		}
		this->_queue.pop();
		this->_visit[x][y][dir] = false;
	}
	int finalDir = 0;
	for (int i = 1; i < 4; ++i)
	{
		if (this->_dist[end.x][end.y][i] < this->_dist[end.x][end.y][finalDir])
		{
			finalDir = i;
		}
	}
	Wire wire;
	if (this->_dist[end.x][end.y][finalDir] == INFL)
	{
		return wire;
	}
	long long status = this->getStatus(end.x, end.y, finalDir);
	vector<CPoint> points;
	points.push_back(CPoint(end.x, end.y));
	while (true)
	{
		int x = getStatusX(status);
		int y = getStatusY(status);
		int dir = getStatusDir(status);
		long long prev = this->_prev[x][y][dir];
		if (prev == -1)
		{
			break;
		}
		int px = getStatusX(prev);
		int py = getStatusY(prev);
		int pdir = getStatusDir(prev);
		if (this->_dist[x][y][dir] - this->_dist[px][py][pdir] > INF)
		{
			points.push_back(CPoint(px, py));
		}
		status = prev;
	}
	points.push_back(CPoint(start.x, start.y));
	for (unsigned int i = points.size() - 1; i >= 0; --i)
	{
		wire.add(points[i].x, points[i].y);
	}
	return wire;
}

/**
 * ��ȡ������ͼ�еĶ�Ӧλ�á�
 * @param box Ҫ���ߵĲ��ߺС�
 * @param id ���ű�š�
 * @return ͼ��λ�á�
 */
CPoint SwitchBoxSolver::getPinGraphPosition(SwitchBox &box, int id)
{
	for (unsigned int i = 0; i < box.pin().size(); ++i)
	{
		if (box.pin()[i].id() == id)
		{
			int shift = (int)(box.pin())[i].shift();
			switch (box.pin()[i].orientation())
			{
			case Pin::ORI_TOP:
				return CPoint(0, shift >> 1);
			case Pin::ORI_BOTTOM:
				return CPoint(this->_row - 1, shift >> 1);
			case Pin::ORI_LEFT:
				return CPoint(shift >> 1, 0);
			case Pin::ORI_RIGHT:
				return CPoint(shift >> 1, this->_col - 1);
			}
		}
	}
	return CPoint(-1, -1);
}

/**
 * ��ȡѹ��״̬��
 * @param x �С�
 * @param y �С�
 * @param dir ����
 * @return ѹ��״̬��
 */
long long SwitchBoxSolver::getStatus(int x, int y, int dir)
{
	return (long long)dir * this->_row * this->_col + x * this->_col + y;
}

/**
 * ��ȡ����
 * @param ѹ��״̬��
 * @return ����
 */
int SwitchBoxSolver::getStatusDir(long long status)
{
	return status / (this->_row * this->_col);
}

/**
 * ��ȡ�С�
  * @param ѹ��״̬��
 * @return �С�
 */
int SwitchBoxSolver::getStatusX(long long status)
{
	return ((status % (this->_row * this->_col)) / this->_col);
}

/**
 * ��ȡ�С�
 * @param ѹ��״̬��
 * @return �С�
 */
int SwitchBoxSolver::getStatusY(long long status)
{
	return status % this->_col;
}

/**
 * ��ȡͼ�е��Ӧ�ڲ��ߺ��е�λ�á�
 * @param x �С�
 * @param y �С�
 * @return ���ߺ��е����ꡣ
 */
CPoint SwitchBoxSolver::getOriginPosition(int x, int y)
{
	return CPoint(x << 1, y << 1);
}