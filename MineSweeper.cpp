#include "StdAfx.h"
#include "MineSweeper.h"

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

void CMineSweeper::Transform(vector<SPoint>& ver,SVector2D& pos,double scale,double rotate)
{
	CMatrix2D matrix;
	matrix.Scale(scale,scale);
	matrix.Rotate(rotate);
	matrix.Translate(pos.x,pos.y);
	matrix.ApplyToShape(ver);
}

void CMineSweeper::Reset()
{
	m_svPosition=SVector2D((double)RandInt(0,CParams::WindowWidth),(double)RandInt(0,CParams::WindowHeight));
	m_dRotation=RandFloat()*CParams::PI*2;
	//m_svLookAt.x=cos(m_dRotation);
	//m_svLookAt.y=sin(m_dRotation);
	m_dSpeed=0;
	m_lTrack=0;
	m_rTrack=0;
	m_dFitness=0;
}

void CMineSweeper::GetClosestMine(vector<CMine>& mine)
{
	double distance=999999999;
	int pos=0;
	for(int i=0;i<mine.size();i++)
	{
		SVector2D poscopy=m_svPosition;
		poscopy-=mine[i].m_svPos;
		double dist=poscopy.Vec2DLenght();
		if (distance>dist)
		{
			distance=dist;
			pos=i;
		}
	}
	SVector2D temppos=m_svPosition-mine[pos].m_svPos;
	m_svClosestMinePos=SVector2D(temppos.Normalize());
	m_iClosestMine=pos;
}

BOOL CMineSweeper::CheckForMine(vector<CMine>& mine)
{		
	SVector2D poscopy=m_svPosition;
		poscopy-=mine[m_iClosestMine].m_svPos;
		double distance=poscopy.Vec2DLenght();
		if (distance<CParams::MineScale)
		{
			return TRUE;
		}
		
	return FALSE;
}

CMineSweeper::CMineSweeper(void)
{	
	for (int i=0;i<NumSweeperVerts;i++)
	{
		m_vecSweeperVertexs.push_back(sweeper[i]);
	}
	m_svPosition=SVector2D((double)RandInt(0,CParams::WindowWidth),(double)RandInt(0,CParams::WindowHeight));
	
	m_dScale=CParams::SweeperScale;

	Reset();

}


CMineSweeper::~CMineSweeper(void)
{
	
}

void CMineSweeper::Update(vector<CMine>& mine)
{
	GetClosestMine(mine);
	if (CheckForMine(mine))
	{
		m_dFitness++;
		mine[m_iClosestMine].m_svPos=SVector2D((double)RandInt(0,CParams::WindowWidth),(double)RandInt(0,CParams::WindowHeight));
		GetClosestMine(mine);
	}
	m_vecInput.clear();
	m_vecInput.push_back(m_svLookAt.x);
	m_vecInput.push_back(m_svLookAt.y);
	m_vecInput.push_back(m_svClosestMinePos.x);
	m_vecInput.push_back(m_svClosestMinePos.y);
	m_vecOutput= m_nnBrain.Update(m_vecInput);
	m_lTrack=m_vecOutput[0];
	m_rTrack=m_vecOutput[1];
	double rotforce=m_lTrack-m_rTrack;
	rotforce=Clamp(rotforce,CParams::MaxRotation);
	m_dSpeed=m_lTrack+m_rTrack;
	m_dRotation+=rotforce;
	m_svLookAt.y=cos(m_dRotation);
	m_svLookAt.x=-sin(m_dRotation);
	m_svPosition+=m_svLookAt*m_dSpeed;
	
	if (m_svPosition.x>CParams::WindowWidth)
	{
		m_svPosition.x=0;
	}
	if (m_svPosition.x<0)
	{
		m_svPosition.x=CParams::WindowWidth;
	}
	if (m_svPosition.y<0)
	{
		m_svPosition.y=CParams::WindowHeight;
	}
	if (m_svPosition.y>CParams::WindowHeight)
	{
		m_svPosition.y=0;
	}
}

void CMineSweeper::Rander(HDC surface,HPEN pen)
{	
	m_hOldPen=(HPEN)SelectObject(surface,pen);
	vector<SPoint>sweepercopy=m_vecSweeperVertexs;
	Transform(sweepercopy,m_svPosition,m_dScale,m_dRotation);
	MoveToEx(surface,sweepercopy[0].x,sweepercopy[0].y,NULL);
	for (int i=0;i<NumSweeperVerts;i++)
	{		
		LineTo(surface,sweepercopy[i].x,sweepercopy[i].y);
	}
	SelectObject(surface,m_hOldPen);
}


