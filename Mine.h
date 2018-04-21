#pragma once
#include "SVector2D.h"
#include "tools.h"
class CMine
{
private:
	vector<SPoint>m_vecMineVB;
	SVector2D m_spMinePos;
	double m_dMineScale;
private:
	void Transform(vector<SPoint>& vbtemp);
public:
	CMine(void);
	~CMine(void);
	void Rander(HDC surface);
	SVector2D GetPos(){return m_spMinePos;}
	void SetPos(){m_spMinePos=SVector2D((double)RandInt(0,CParams::WindowWidth-1),(double)RandInt(0,CParams::WindowHeight-1));}
};

