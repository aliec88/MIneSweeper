#pragma once
class CTimer
{
private:
	LONGLONG m_llCounterPerFps;
	LONGLONG m_llNextTime;
public:
	CTimer(void);
	~CTimer(void);
	void Start();
	BOOL ReadyForNextTime();
};

