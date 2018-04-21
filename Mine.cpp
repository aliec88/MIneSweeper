#include "StdAfx.h"
#include "Mine.h"

const int NumMineVertex=4;
const SPoint mine[NumMineVertex]={SPoint(-1,-1),SPoint(-1,1),SPoint(1,1),SPoint(1,-1)};

void CMine::Transform(vector<SPoint>& vbtemp)
{
	CMatrix2D matrix;
	matrix.Scale(m_dMineScale,m_dMineScale);
	matrix.Translate(m_spMinePos.x,m_spMinePos.y);
	matrix.ApplyToShape(vbtemp);
}

CMine::CMine(void)
{
	for (int i=0;i<NumMineVertex;i++)
	{
		m_vecMineVB.push_back(mine[i]);
	}
	m_spMinePos=SVector2D((double)RandInt(0,CParams::WindowWidth-1),(double)RandInt(0,CParams::WindowHeight-1));
	m_dMineScale=CParams::MineScale;
}


CMine::~CMine(void)
{
}

void CMine::Rander(HDC surface)
{
	vector<SPoint>vbtemp=m_vecMineVB;
	Transform(vbtemp);
	MoveToEx(surface,vbtemp[0].x,vbtemp[0].y,NULL);
	for (int i=0;i<vbtemp.size();i++)
	{
		LineTo(surface,vbtemp[i].x,vbtemp[i].y);
	}
	LineTo(surface,vbtemp[0].x,vbtemp[0].y);

}
