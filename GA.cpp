#include "StdAfx.h"
#include "GA.h"


void CGA::CaculateFitness()
{
	double best=0;
	for (int i=0;i<CParams::Population;i++)
	{
		if (best<m_vecPopulation[i].m_dFitness)
		{
			best=m_vecPopulation[i].m_dFitness;
		}
		m_dTotalFitness+=m_vecPopulation[i].m_dFitness;
	}
	m_dAverageFitness=m_dTotalFitness/CParams::Population;
	m_dBestFitness=best;
}

void CGA::GrabBest(vector<SChromsome>& newpop,int num)
{
	sort(m_vecPopulation.begin(),m_vecPopulation.end());
	for (int i=0;i<num;i++)
	{
		newpop.push_back(m_vecPopulation[m_vecPopulation.size()-i-1]);
	}
}

SChromsome CGA::RouletteSelect()
{
	double slice=RandFloat()*m_dTotalFitness;
	SChromsome temp;
	double fitenesstmp=0;
	for (int i=0;i<CParams::Population;i++)
	{
		fitenesstmp+=m_vecPopulation[i].m_dFitness;
		if (fitenesstmp>=slice)
		{
			temp=m_vecPopulation[i];
			break;
		}
	}
	return temp;

}

void CGA::Crossover(const vector<double>& mum,const vector<double>& dad,vector<double>&baby1,vector<double>&baby2)
{
	if (RandFloat()>CParams::CrossoverRate || mum==dad)
	{
		baby1=mum;
		baby2=dad;
		return;
	}
	int pos1=m_vecSplitPos[RandInt(0,m_vecSplitPos.size()/2)];
	int pos2=m_vecSplitPos[RandInt(m_vecSplitPos.size()/2+1,m_vecSplitPos.size()-1)];
	for (int i=0;i<mum.size();i++)
	{
		if (i<pos1 || i>=pos2)
		{
			baby1.push_back(mum[i]);
			baby2.push_back(dad[i]);
		}else
		{
			baby1.push_back(dad[i]);
			baby2.push_back(mum[i]);
		}
	}
}

void CGA::Mutate(vector<double>& chromgenbit)
{
	for (int i=0;i<chromgenbit.size();i++)
	{
		if (RandFloat()<CParams::MutateRate)
		{
			chromgenbit[i]+=RanddomClamped()*CParams::MaxPerturbation;
		}
	}
}

void CGA::Epoch(vector<SChromsome>& oldpop)
{
	Reset();
	m_vecPopulation=oldpop;
	CaculateFitness();
	vector<SChromsome>newpop;
	GrabBest(newpop,CParams::ElitismNumber);
	while(newpop.size()<CParams::Population)
	{
		SChromsome mum=RouletteSelect();
		SChromsome dad=RouletteSelect();
		SChromsome baby1,baby2;
		Crossover(mum.m_vecGenBit,dad.m_vecGenBit,baby1.m_vecGenBit,baby2.m_vecGenBit);
		Mutate(baby1.m_vecGenBit);
		Mutate(baby2.m_vecGenBit);
		newpop.push_back(baby1);
		newpop.push_back(baby2);
	}
	m_vecPopulation=newpop;
}

void CGA::Reset()
{
	m_dTotalFitness=0;
	m_dBestFitness=0;
	m_dAverageFitness=0;
}

CGA::CGA(int genlength,vector<int>&splitPos)
{
	m_iGenLenght=genlength;
	for (int i=0;i<CParams::Population;i++)
	{
		m_vecPopulation.push_back(SChromsome(m_iGenLenght));
	}
	m_dBestFitness=0;
	m_dAverageFitness=0;
	m_dTotalFitness=0;
	m_vecSplitPos=splitPos;
}


CGA::~CGA(void)
{
}

vector<SChromsome>& CGA::Update(vector<SChromsome>& oldpop)
{
	Epoch(oldpop);
	return m_vecPopulation;
}

SChromsome::SChromsome(int genlength):m_dFitness(0)
{
	for (int i=0;i<genlength;i++)
	{
		m_vecGenBit.push_back(RanddomClamped());
	}
}
