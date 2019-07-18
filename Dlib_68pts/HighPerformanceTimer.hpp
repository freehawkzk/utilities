#pragma once
#include "windows.h"
/************************************************************************/
/*
*  Class name : CHighPerformanceTimer
*      This is a high performance timer on windows platform. The result unit
*  is second.
*/
/************************************************************************/
class  CHighPerformanceTimer
{
public:

    CHighPerformanceTimer(char* name,int nLength, bool show = false); 

    ~CHighPerformanceTimer();

    void Show();

    double GetTime();
    static void DontShowAll()
    {
        CHighPerformanceTimer::bNotShowAll = true;
    }
protected:
private:
    CHighPerformanceTimer() = delete;
    CHighPerformanceTimer(CHighPerformanceTimer& oth) = delete;
    CHighPerformanceTimer& operator=(CHighPerformanceTimer&oth) = delete;
    double dT;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLastTime1;
    LARGE_INTEGER nLastTime2;
    char name[MAX_PATH];
    bool bShown = false;
    static bool bNotShowAll ;
};