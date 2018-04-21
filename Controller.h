#pragma once
class CController
{
private:
	BOOL m_bFast;
	vector<CMine>m_vecMine;
	vector<CSweeper>m_vecSweepers;
	HPEN m_hRedPen;
	HPEN m_hGreenPen;
	HPEN m_hOldPen;
	int m_iTick;
	CGA m_cGA;
	vector<SChromsome>m_vecPopulationCopy;
	int m_iEpoch;
	vector<double>m_vecBestFitness;
	vector<double>m_vecAverFitness;
private:
	void DrawChart(HDC surface);
public:
	CController(void);
	~CController(void);
	void Update();
	void Rander(HDC surface);
	void ToggleFast();
	BOOL GetFast(){return m_bFast;}
};

