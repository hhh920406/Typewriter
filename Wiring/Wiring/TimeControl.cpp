#include "stdafx.h"
#include <fstream>
#include "TimeControl.h"
using namespace std;

TimeControl::TimeControl()
{
}


TimeControl::~TimeControl()
{
}

int TimeControl::getTime()
{
    int time;
    ifstream in;
    in.open("config");
    in >> time;
    in.close();
    return time;
}

void TimeControl::saveTime(int time)
{
    ofstream out;
    out.open("config");
    out << time << endl << flush;
    out.close();
}