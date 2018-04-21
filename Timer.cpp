#include "StdAfx.h"
#include "Timer.h"


CTimer::CTimer(void)
{
	LONGLONG frequency;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	m_llCounterPerFps=(LONGLONG)(frequency/CParams::FPS);
	m_llNextTime=0;
}


CTimer::~CTimer(void)
{
}

void CTimer::Start()
{
	LONGLONG current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	m_llNextTime=current+m_llCounterPerFps;
}

BOOL CTimer::ReadyForNextTime()
{
	LONGLONG current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	if (m_llNextTime<current)
	{
		m_llNextTime=current+m_llCounterPerFps;
		return TRUE;
	}
	return FALSE;
}
