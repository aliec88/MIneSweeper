#include "StdAfx.h"
#include "Timer.h"


CTimer::CTimer(double fps)
{
	LONGLONG coutpersecond;
	QueryPerformanceFrequency((LARGE_INTEGER*)&coutpersecond);
	m_dTimeScale=1.0f/coutpersecond;
	m_llCountPerFPS=(LONGLONG)(coutpersecond/fps);
}


CTimer::~CTimer(void)
{
}

void CTimer::Start()
{
	LONGLONG current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	m_llNextTime=current+m_llCountPerFPS;
	m_llLastTime=current;
}

BOOL CTimer::ReadyForNextTime()
{
	LONGLONG current;
	QueryPerformanceCounter((LARGE_INTEGER*)&current);
	if (current>m_llNextTime)
	{
		m_llNextTime=current+m_llCountPerFPS;
		m_dTimeElapsed=(current-m_llLastTime)*m_dTimeScale;
		m_llLastTime=current;
		return TRUE;
	}
	return FALSE;
}
