#include "HighPerformanceTimer.hpp"
#include <iostream>

bool CHighPerformanceTimer::bNotShowAll = false;
CHighPerformanceTimer::CHighPerformanceTimer(char* pname, int nLength, bool show/* = false*/) :dT(0)
{
    bShown = show;
    strcpy_s(this->name, (nLength +1)* sizeof(char), pname);
    QueryPerformanceFrequency(&nFreq);
    QueryPerformanceCounter(&nLastTime1);
    if (bShown && !CHighPerformanceTimer::bNotShowAll)
    {
        std::cout << "start timer: " << name << std::endl;
    }
}

CHighPerformanceTimer::~CHighPerformanceTimer()
{
    if (bShown && !CHighPerformanceTimer::bNotShowAll)
    {
        QueryPerformanceCounter(&nLastTime2);
        dT = (nLastTime2.QuadPart - nLastTime1.QuadPart) / (double)nFreq.QuadPart;
        std::cout << "end   timer: " << name << " : " << dT << std::endl;
    }
}

void CHighPerformanceTimer::Show()
{
    std::cout << "show  timer: " << name << " : " << GetTime() << std::endl;
}

double CHighPerformanceTimer::GetTime()
{
    QueryPerformanceCounter(&nLastTime2);
    dT = (nLastTime2.QuadPart - nLastTime1.QuadPart) / (double)nFreq.QuadPart;
    return dT;
}