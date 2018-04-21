#include "StdAfx.h"
#include "Controller.h"


void CController::DrawChart(HDC surface)
{
	
	wstring s=TEXT("最好分值：")+ftos(m_cGA.GetBestFitness());
	TextOut(surface,0,20,s.c_str(),s.size());
	s=TEXT("平均分值：")+ftos(m_cGA.GetAverFitness());
	TextOut(surface,0,40,s.c_str(),s.size());
	double Hscale=CParams::WindowWidth/(m_iEpoch+1);
	double Vscale=CParams::WindowHeight/((m_cGA.GetBestFitness()+1)*2);
	float x=0;
	m_hOldPen=(HPEN)SelectObject(surface,m_hRedPen);
	MoveToEx(surface,0,CParams::WindowHeight,NULL);
	for (int i=0;i<m_vecBestFitness.size();i++)
	{
		LineTo(surface,(int)x,(int)(CParams::WindowHeight- m_vecBestFitness[i]*Vscale));
		x+=Hscale;
	}
	x=0;
	SelectObject(surface,m_hOldPen);
	m_hOldPen=(HPEN)SelectObject(surface,m_hGreenPen);
	MoveToEx(surface,0,CParams::WindowHeight,NULL);
	for (int i=0;i<m_vecAverFitness.size();i++)
	{
		LineTo(surface,(int)x,(int)(CParams::WindowHeight- m_vecAverFitness[i]*Vscale));
		x+=Hscale;
	}
	SelectObject(surface,m_hOldPen);
}

CController::CController(void)
{
	for (int i=0;i<CParams::MineNumber;i++)
	{
		m_vecMine.push_back(CMine());
	}
	for (int i=0;i<CParams::SweeperNumber;i++)
	{
		m_vecSweepers.push_back(CSweeper());
	}
	int genlength=m_vecSweepers[0].GetWeightNum();
	vector<int>splitpos=m_vecSweepers[0].GetSplitPos();
	m_cGA=CGA(genlength,splitpos);	
	m_vecPopulationCopy=m_cGA.GetPopulation();
	for (int i=0;i<m_vecPopulationCopy.size();i++)
	{
		m_vecSweepers[i].PutWeight(m_vecPopulationCopy[i].m_vecGenBit);
	}

	m_hGreenPen=CreatePen(PS_SOLID,1,RGB(0,255,0));
	m_hRedPen=CreatePen(PS_SOLID,1,RGB(255,0,0));
	m_bFast=FALSE;
	m_iTick=0;
	m_iEpoch=0;
}


CController::~CController(void)
{
	DeleteObject(m_hRedPen);
	DeleteObject(m_hGreenPen);
}

void CController::Update()
{
	if (m_iTick<CParams::TickNumber)
	{
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			m_vecSweepers[i].Update(m_vecMine);
		}
		m_iTick++;
	}else
	{
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			m_vecPopulationCopy[i].m_dFitness=m_vecSweepers[i].GetFiteness();
		}
		m_vecPopulationCopy=m_cGA.Update(m_vecPopulationCopy);
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			m_vecSweepers[i].PutWeight(m_vecPopulationCopy[i].m_vecGenBit);
			m_vecSweepers[i].Reset();
		}
		m_iTick=0;
		m_iEpoch++;
		m_vecBestFitness.push_back(m_cGA.GetBestFitness());
		m_vecAverFitness.push_back(m_cGA.GetAverFitness());
	}
}

void CController::Rander(HDC surface)
{
	wstring s=TEXT("时代：")+itos(m_iEpoch);
	TextOut(surface,0,0,s.c_str(),s.size());
	if (!m_bFast)
	{
		m_hOldPen=(HPEN)SelectObject(surface,m_hGreenPen);
		for (int i=0;i<m_vecMine.size();i++)
		{
			m_vecMine[i].Rander(surface);
		}
		SelectObject(surface,m_hOldPen);

		m_hOldPen=(HPEN)SelectObject(surface,m_hRedPen);
		for (int i=0;i<m_vecSweepers.size();i++)
		{
			if (i>=CParams::ElitismNumber)
			{
			  SelectObject(surface,m_hOldPen);
			}
			m_vecSweepers[i].Rander(surface);
		}
	} 
	else
	{
		DrawChart(surface);
	}
}

void CController::ToggleFast()
{
	if (m_bFast)
	{
		m_bFast=FALSE;
	}else
	{
		m_bFast=TRUE;
	}
}
