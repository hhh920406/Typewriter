#include "stdafx.h"
#include <ctime>
#include <algorithm>
#include "SwitchBoxSolver.h"
using namespace std;
const long long INF = 0x3f3f3f3fLL;
const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
const int DIR_X[4] = { -1, 0, 1, 0 };
const int DIR_Y[4] = { 0, 1, 0, -1 };
const int MARGIN = 5;
const int PADDING = 5;

SwitchBoxSolver::SwitchBoxSolver()
{
	this->_time = 0;
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
	DWORD start = GetTickCount();
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
	DWORD end = GetTickCount();
	this->_time = end - start;
	return greedyWire;
}

/**
 * ��ȡ�ϴ��㷨��ʱ��
 * @return ʱ��
 */
int SwitchBoxSolver::getElapsedTime() const
{
	return this->_time;
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
		for (unsigned int j = 0; j < pin.size(); ++j)
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

	this->_row = box.height() / MARGIN;
	this->_col = box.width() / MARGIN;
	for (int i = 0; i < this->_row; ++i)
	{
		this->_graph.push_back(vector<bool>());
		this->_dist.push_back(vector< vector<long long> >());
		this->_prev.push_back(vector< vector<long long> >());
		this->_visit.push_back(vector< vector<bool> >());
		for (int j = 0; j < this->_col; ++j)
		{
			this->_graph[i].push_back(false);
			this->_dist[i].push_back(vector<long long>(4));
			this->_prev[i].push_back(vector<long long>(4));
			this->_visit[i].push_back(vector<bool>(4));
		}
	}

	for (int i = PADDING; i < this->_row - PADDING; ++i)
	{
		for (int j = PADDING; j < this->_col - PADDING; ++j)
		{
			this->_graph[i][j] = true;
		}
	}
	for (unsigned int i = 0; i < box.pin().size(); ++i)
	{
		CPoint pos = this->getPinGraphPosition(box, box.pin()[i].id());
		switch (box.pin()[i].orientation())
		{
		case Pin::ORI_TOP:
			for (int j = 0; j < PADDING; ++j)
			{
				this->_graph[j][pos.y] = true;
			}
			break;
		case Pin::ORI_BOTTOM:
			for (int j = 0; j < PADDING; ++j)
			{
				this->_graph[this->_row - j - 1][pos.y] = true;
			}
			break;
		case Pin::ORI_LEFT:
			for (int j = 0; j < PADDING; ++j)
			{
				this->_graph[pos.x][j] = true;
			}
			break;
		case Pin::ORI_RIGHT:
			for (int j = 0; j < PADDING; ++j)
			{
				this->_graph[pos.x][this->_col - j - 1] = true;
			}
			break;
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
	if (this->_dealt[u] || this->_dealt[v])
	{
		return INF;
	}
	if (u == -1 || v == -1)
	{
		return -1;
	}
	int count1 = 0;
	for (int i = u + 1; ; ++i)
	{
		if (i >= (int)this->_pinPosition.size())
		{
			i = 0;
		}
		if (i == v)
		{
			break;
		}
		count1 += !this->_dealt[i];
	}
	int count2 = 0;
	for (int i = u - 1; ; --i)
	{
		if (i < 0)
		{
			i = this->_pinPosition.size() - 1;
		}
		if (i == v)
		{
			break;
		}
		count2 += !this->_dealt[i];
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
	int pu = this->getPinPosition(u);
	int pv = this->getPinPosition(v);
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
	int startDir = this->getStartOrientation(box, u);
	this->_dist[start.x][start.y][startDir] = 0;
	this->_visit[start.x][start.y][startDir] = true;
	this->_queue.push(this->getStatus(start.x, start.y, startDir));
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
					if (this->_graph[tx][ty])
					{
						long long dist = this->_dist[x][y][dir] + 1;
						if (dir != i)
						{
							dist += INF;
						}
						if (dist < this->_dist[tx][ty][i])
						{
							this->_dist[tx][ty][i] = dist;
							this->_prev[tx][ty][i] = status;
							if (!this->_visit[tx][ty][i])
							{
								this->_visit[tx][ty][i] = true;
								this->_queue.push(this->getStatus(tx, ty, i));
							}
						}
					}
				}
			}
		}
		this->_queue.pop();
		this->_visit[x][y][dir] = false;
	}
	int endDir = this->getStartOrientation(box, v);
	int finalDir = -1;
	long long finalDist = INFL;
	for (int i = 0; i < 4; ++i)
	{
		if (this->_dist[end.x][end.y][i] == INFL)
		{
			continue;
		}
		long long dist = this->_dist[end.x][end.y][i];
		if (i != finalDir)
		{
			dist += INF;
		}
		if (dist < finalDist)
		{
			finalDist = dist;
			finalDir = i;
		}
	}
	Wire wire;
	if (finalDir == -1)
	{
		return wire;
	}
	long long status = this->getStatus(end.x, end.y, finalDir);
	vector<CPoint> points;
	points.push_back(CPoint(getOriginPosition(end.x, end.y)));
	while (true)
	{
		int x = getStatusX(status);
		int y = getStatusY(status);
		int dir = getStatusDir(status);
		long long prev = this->_prev[x][y][dir];
		this->_graph[x][y] = false;
		if (prev == -1)
		{
			break;
		}
		int px = getStatusX(prev);
		int py = getStatusY(prev);
		int pdir = getStatusDir(prev);
		if (this->_dist[x][y][dir] - this->_dist[px][py][pdir] > INF)
		{
			points.push_back(CPoint(getOriginPosition(px, py)));
		}
		status = prev;
	}
	points.push_back(CPoint(getOriginPosition(start.x, start.y)));
	for (int i = points.size() - 1; i >= 0; --i)
	{
		if (i < (int)(points.size() - 1))
		{
			if (points[i].x == points[i + 1].x && points[i].y == points[i + 1].y)
			{
				continue;
			}
		}
		wire.add(points[i].y, points[i].x);
	}
	this->_dealt[pu] = true;
	this->_dealt[pv] = true;
	wire.setU(u);
	wire.setV(v);
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
				return CPoint(0, shift / MARGIN);
			case Pin::ORI_BOTTOM:
				return CPoint(this->_row - 1, shift / MARGIN);
			case Pin::ORI_LEFT:
				return CPoint(shift / MARGIN, 0);
			case Pin::ORI_RIGHT:
				return CPoint(shift / MARGIN, this->_col - 1);
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
	return (int)(status / (this->_row * this->_col));
}

/**
 * ��ȡ�С�
  * @param ѹ��״̬��
 * @return �С�
 */
int SwitchBoxSolver::getStatusX(long long status)
{
	return (int)(((status % (this->_row * this->_col)) / this->_col));
}

/**
 * ��ȡ�С�
 * @param ѹ��״̬��
 * @return �С�
 */
int SwitchBoxSolver::getStatusY(long long status)
{
	return (int)(status % this->_col);
}

/**
 * ��ȡͼ�е��Ӧ�ڲ��ߺ��е�λ�á�
 * @param x �С�
 * @param y �С�
 * @return ���ߺ��е����ꡣ
 */
CPoint SwitchBoxSolver::getOriginPosition(int x, int y)
{
	return CPoint(x * MARGIN, y * MARGIN);
}

/**
 * ��ȡ��ʼ���������ŷ����෴��
 * @param box Ҫ���ߵĲ��ߺС�
 * @param id ���ű�š�
 * @return ��ʼ����
 */
int SwitchBoxSolver::getStartOrientation(SwitchBox &box, int id)
{
	switch (box.pin()[this->getPinPosition(id)].orientation())
	{
	case Pin::ORI_TOP:
		return Pin::ORI_BOTTOM;
	case Pin::ORI_BOTTOM:
		return Pin::ORI_TOP;
	case Pin::ORI_LEFT:
		return Pin::ORI_RIGHT;
	case Pin::ORI_RIGHT:
		return Pin::ORI_LEFT;
	}
	return -1;
}