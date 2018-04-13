#pragma once
class CTimer
{
private:
	double m_dTimeScale;
	double m_dFPS;
	double m_dTimeElapsed;
	LONGLONG m_llCountPerFPS;
	LONGLONG m_llNextTime;
	LONGLONG m_llLastTime;

public:
	CTimer(double fps);
	~CTimer(void);
	void Start();
	BOOL ReadyForNextTime();
	double GetTimeElapsed(){return m_dTimeElapsed;}
};

