#include "StdAfx.h"
#include "Sweeper.h"

const int NumSweeperVerts = 16;
const SPoint sweeper[NumSweeperVerts] = {SPoint(-1, -1),
	SPoint(-1, 1),
	SPoint(-0.5, 1),
	SPoint(-0.5, -1),

	SPoint(0.5, -1),
	SPoint(1, -1),
	SPoint(1, 1),
	SPoint(0.5, 1),

	SPoint(-0.5, -0.5),
	SPoint(0.5, -0.5),

	SPoint(-0.5, 0.5),
	SPoint(-0.25, 0.5),
	SPoint(-0.25, 1.75),
	SPoint(0.25, 1.75),
	SPoint(0.25, 0.5),
	SPoint(0.5, 0.5)};

void CSweeper::Transform(vector<SPoint>& vbtmp)
{
	CMatrix2D matrix;
	matrix.Scale(m_dScale,m_dScale);
	matrix.Rotate(m_dRotation);
	matrix.Translate(m_svPos.x,m_svPos.y);
	matrix.ApplyToShape(vbtmp);
}

SVector2D& CSweeper::GetClosestMine(vector<CMine>& mine)
{
	double dis=99999999;
	int pos=0;
	SVector2D temp(0,0);
	for (int i=0;i<mine.size();i++)
	{
		if (dis>m_svPos.Getdistance(mine[i].GetPos()))
		{
			dis=m_svPos.Getdistance(mine[i].GetPos());
			pos=i;
		}
	}
	m_iClosestMineIndex=pos;
	temp=m_svPos-mine[m_iClosestMineIndex].GetPos();
	temp=temp.Normalize();
	return temp;
}

BOOL CSweeper::CheckClosestMine(vector<CMine>&mine)
{
	double distance=m_svPos.Getdistance(mine[m_iClosestMineIndex].GetPos());
	if (distance<CParams::MineScale*2)
	{
		return TRUE;
	}
	return FALSE;
}

CSweeper::CSweeper(void)
{
	for (int i=0;i<NumSweeperVerts;i++)
	{
		m_vecSweeperVB.push_back(sweeper[i]);
	}
	m_dScale=CParams::SweeperScale;
	m_dLTrack=0.16;
	m_dRTrack=0.16;
	Reset();
}


CSweeper::~CSweeper(void)
{
}

void CSweeper::Rander(HDC surface)
{
	vector<SPoint>vbtmp=m_vecSweeperVB;
	Transform(vbtmp);
	MoveToEx(surface,vbtmp[0].x,vbtmp[0].y,NULL);
	for (int i=0;i<vbtmp.size();i++)
	{
		LineTo(surface,vbtmp[i].x,vbtmp[i].y);
	}
	LineTo(surface,vbtmp[0].x,vbtmp[0].y);
}

void CSweeper::Update(vector<CMine>& mine)
{
	SVector2D svclosestmine= GetClosestMine(mine);
	if (CheckClosestMine(mine))
	{
		mine[m_iClosestMineIndex].SetPos();
		m_dFitness++;
	}else
	{
		vector<double>input;
		double dot=m_svLookat.Dot(svclosestmine);
		int s=m_svLookat.sign(m_svClosestMine);
		input.push_back(dot*s);
		vector<double> output= m_nnBrain.Update(input);
		m_dLTrack=output[0];
		m_dRTrack=output[1];
		double force=m_dLTrack-m_dRTrack;
		Clamp(force,-CParams::MaxSpeed,CParams::MaxSpeed);
		m_dRotation+=force;
		double speed=m_dLTrack+m_dRTrack;
		m_svLookat.x=-sin(m_dRotation);
		m_svLookat.y=cos(m_dRotation);
		SVector2D temp=m_svLookat*speed;
		//m_svPos+=(m_svLookat*speed);
		m_svPos+=temp;
		if (m_svPos.x>CParams::WindowWidth)
		{
			m_svPos.x=0;
		}
		if (m_svPos.x<0)
		{
			m_svPos.x=CParams::WindowWidth;
		}
		if (m_svPos.y<0)
		{
			m_svPos.y=CParams::WindowHeight;
		}
		if (m_svPos.y>CParams::WindowHeight)
		{
			m_svPos.y=0;
		}
	}

}

void CSweeper::Reset()
{
	m_svPos=SVector2D((double)RandInt(0,CParams::WindowWidth-1),(double)RandInt(0,CParams::WindowHeight-1));
	m_dRotation=RandFloat()*CParams::PI*2;
	m_dFitness=0;
	
}

