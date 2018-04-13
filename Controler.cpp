#include "StdAfx.h"
#include "Controler.h"


void CControler::DrawChart(HDC surface)
{
	wstring s=TEXT("Best Fitness: ")+ftos(m_pGA->GetBestFitness());
	TextOut(surface,5,20,s.c_str(),s.size());
	s=TEXT("Average Fitness: ")+ftos(m_pGA->GetAverFitness());
	TextOut(surface,5,40,s.c_str(),s.size());
	s=TEXT("Generation: ")+ftos(m_iEpoch);
	TextOut(surface,5,0,s.c_str(),s.size());

	double HScale=(double)m_ixClient/(m_iEpoch+1);
	double VScale=(double)m_iyClient/((m_pGA->GetBestFitness()+1)*2);
	double x=0;
	m_OldPen=(HPEN)SelectObject(surface,m_RedPen);
	MoveToEx(surface,0,m_iyClient,NULL);
	for (int i=0;i<m_vecBestFitness.size();i++)
	{
		LineTo(surface,x,m_iyClient-VScale*m_vecBestFitness[i]);
		x+=HScale;
	}
	SelectObject(surface,m_OldPen);
	m_OldPen=(HPEN)SelectObject(surface,m_BluePen);
	MoveToEx(surface,0,m_iyClient,NULL);
	x=0;
	for(int i=0;i<m_vecAverFitness.size();i++)
	{
		LineTo(surface,x,m_iyClient-VScale*m_vecAverFitness[i]);
		x+=HScale;
	}
	SelectObject(surface,m_OldPen);
}

void CControler::Transform(vector<SPoint>& ver,SVector2D& pos,double scale,double rotate)
{
	CMatrix2D matrix;
	matrix.Scale(scale,scale);
	matrix.Rotate(rotate);
	matrix.Translate(pos.x,pos.y);
	matrix.ApplyToShape(ver);
}

CControler::CControler(void)
{	
	for (int i=0;i<CParams::NumberMines;i++)
	{
		m_vecMine.push_back(CMine());
	}
	for (int i=0;i<CParams::PopulationNumber;i++)
	{
		m_vecSweepers.push_back(CMineSweeper());
	}
	m_dNumberWeight=m_vecSweepers[0].GetWeightNum();
	m_pGA=new CGA(m_dNumberWeight);
	m_vecPopCopy=m_pGA->GetPopulation();
	for (int i=0;i<m_vecSweepers.size();i++)
	{
		m_vecSweepers[i].PutWeights(m_vecPopCopy[i].m_vecGenBit);
	}
	m_iEpoch=0;
	m_iTick=0;
	m_ixClient=CParams::WindowWidth;
	m_iyClient=CParams::WindowHeight;
	m_RedPen=CreatePen(PS_SOLID,1,RGB(255,0,0));
	m_BluePen=CreatePen(PS_SOLID,1,RGB(0,0,255));
	m_GreenPen=CreatePen(PS_SOLID,1,RGB(0,255,0));
	m_bFast=FALSE;
}


CControler::~CControler(void)
{
	delete m_pGA;
	DeleteObject(m_RedPen);
	DeleteObject(m_BluePen);
	DeleteObject(m_OldPen);
}

void CControler::Update()
{
	if (m_iTick<CParams::TickNumber)
	{
		m_iTick++;
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			m_vecSweepers[i].Update(m_vecMine);			
		}
	}else
	{
		m_iTick=0;
		m_iEpoch++;
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			m_vecPopCopy[i].m_dFitness=m_vecSweepers[i].GetFitness();
		}
		m_vecPopCopy=m_pGA->Update(m_vecPopCopy);
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			m_vecSweepers[i].PutWeights(m_vecPopCopy[i].m_vecGenBit);
			m_vecSweepers[i].Reset();
		}
		m_vecBestFitness.push_back(m_pGA->GetBestFitness());
		m_vecAverFitness.push_back(m_pGA->GetAverFitness());
	}
}

void CControler::Rander(HDC surface)
{
	if (!GetFast())
	{
		m_OldPen=(HPEN)SelectObject(surface,m_GreenPen);
		vector<CMine>MineCopy=m_vecMine;
		for (int i=0;i<MineCopy.size();i++)
		{
			Transform(MineCopy[i].m_vecMineVertexs,MineCopy[i].m_svPos,CParams::MineScale,0);
			MoveToEx(surface,MineCopy[i].m_vecMineVertexs[0].x,MineCopy[i].m_vecMineVertexs[0].y,NULL);
			for (int j=0;j<MineCopy[i].m_vecMineVertexs.size();j++)
			{
				LineTo(surface,MineCopy[i].m_vecMineVertexs[j].x,MineCopy[i].m_vecMineVertexs[j].y);
			}
			LineTo(surface,MineCopy[i].m_vecMineVertexs[0].x,MineCopy[i].m_vecMineVertexs[0].y);
		}
		SelectObject(surface,m_OldPen);
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			if (i<CParams::NumberElitism)
			{
				m_vecSweepers[i].Rander(surface,m_RedPen);
			}else
			{
				m_OldPen=(HPEN)SelectObject(surface,GetStockObject(BLACK_PEN));
				m_vecSweepers[i].Rander(surface,m_OldPen);
			}
		}
		wstring txt=TEXT("°´F¼ü¼ÓËÙ");
		TextOut(surface,0,330,txt.c_str(),txt.size());
	}else
	{
		DrawChart(surface);
	}
	
}
