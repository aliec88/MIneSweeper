#pragma once

class CControler
{
private:
	vector<CMineSweeper>m_vecSweepers;
	vector<SChromosome>m_vecPopCopy;
	vector<double>m_vecBestFitness;
	vector<double>m_vecAverFitness;
	vector<CMine>m_vecMine;	

	CGA* m_pGA;
	int m_iEpoch;
	int m_iTick;
	BOOL m_bFast;
	int m_ixClient;
	int m_iyClient;
	HPEN m_OldPen;
	HPEN m_RedPen;
	HPEN m_BluePen;
	HPEN m_GreenPen;
	double m_dNumberWeight;
private:
	void DrawChart(HDC surface);
	void Transform(vector<SPoint>& ver,SVector2D& pos,double scale,double rotate);

public:
	CControler(void);
	~CControler(void);
	void Update();
	void Rander(HDC surface);
	void ToggleFast()
	{
		if (m_bFast==TRUE)
		{
			m_bFast= FALSE;
		}else
		{
			m_bFast= TRUE;
		}
	}
	BOOL GetFast(){return m_bFast;}
};

