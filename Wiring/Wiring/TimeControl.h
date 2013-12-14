/**
 * 记录和读取动画时间间隔。
 * @author ZHG <CyberZHG@gmail.com>
 */

#pragma once
class TimeControl
{
public:
    TimeControl();
    virtual ~TimeControl();
    
    static int getTime();
    static void saveTime(int time);
};

