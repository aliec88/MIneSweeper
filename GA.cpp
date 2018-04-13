#include "StdAfx.h"
#include "GA.h"


void CGA::CreatePopulation()
{
	for (int i=0;i<m_iPopNum;i++)
	{
		m_vecPopulation.push_back(SChromosome());
		for (int j=0;j<m_iChromLenght;j++)
		{
			m_vecPopulation[i].m_vecGenBit.push_back(RandomClamped());
		}
	}
}





void CGA::Best(int num,vector<SChromosome>&newPop)
{
	sort(m_vecPopulation.begin(),m_vecPopulation.end());
	for (int i=0;i<num;i++)
	{
		newPop.push_back(m_vecPopulation[m_vecPopulation.size()-i-1]);
	}
}

SChromosome CGA::RoultteSelect()
{
	double slice=RandFloat()*m_dTotalFitness;
	SChromosome temp;
	double f=0;
	for (int i=0;i<m_iPopNum;i++)
	{
		f+=m_vecPopulation[i].m_dFitness;
		if (f>slice)
		{
			temp=m_vecPopulation[i];
			break;
		}
	}
	return temp;
}

void CGA::Crossover(const vector<double>&dad,const vector<double>&mum,vector<double>&baby1,vector<double>&baby2)
{
	if (RandFloat()>m_dCrossoverRate || mum==dad)
	{
		baby1=mum;
		baby2=dad;
		return;
	}
	int pos=RandInt(0,m_iChromLenght);
	for (int i=0;i<pos;i++)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}
	for (int i=pos;i<m_iChromLenght;i++)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
}

void CGA::Mutate(vector<double>& chrom)
{
	for (int i=0;i<chrom.size();i++)
	{
		if (RandFloat()<m_dMutationRate)
		{
			chrom[i]+=RandomClamped()*CParams::MaxPerturbation;
		}
	}
}

void CGA::CaculateFitness()
{
	m_dTotalFitness=0;
	m_dBestFitness=0;
	m_dWorstFitness=99999;
	for (int i=0;i<m_iPopNum;i++)
	{
		if (m_dBestFitness< m_vecPopulation[i].m_dFitness)
		{
			m_dBestFitness=m_vecPopulation[i].m_dFitness;
		}
		if (m_dWorstFitness>m_vecPopulation[i].m_dFitness)
		{
			m_dWorstFitness=m_vecPopulation[i].m_dFitness;
		}
		m_dTotalFitness+=m_vecPopulation[i].m_dFitness;
	}
	m_dAverageFitness=m_dTotalFitness/m_iPopNum;
}

CGA::CGA(double chromlength)
{
	m_iPopNum=CParams::PopulationNumber;
	m_iChromLenght=chromlength;
	m_dCrossoverRate=CParams::CrossoverRate;
	m_dMutationRate=CParams::MutationRate;
	CreatePopulation();
	m_dBestFitness=0;
	m_dAverageFitness=0;
}


CGA::~CGA(void)
{
}

vector<SChromosome> CGA::Update(vector<SChromosome>& Popcopy)
{
	return Epoch(Popcopy);
}

vector<SChromosome> CGA::Epoch(vector<SChromosome>& OldPopulation)
{
	m_vecPopulation=OldPopulation;
	CaculateFitness();
	vector<SChromosome>newPopulation;
	Best(CParams::NumberElitism,newPopulation);
	while(newPopulation.size()<m_iPopNum)
	{
		SChromosome mum=RoultteSelect();
		SChromosome dad=RoultteSelect();
		vector<double> baby1,baby2;
		Crossover(dad.m_vecGenBit,mum.m_vecGenBit,baby1,baby2);
		Mutate(baby1);
		Mutate(baby2);
		newPopulation.push_back(SChromosome(baby1,0));
		newPopulation.push_back((SChromosome(baby2,0)));
	}
	m_vecPopulation=newPopulation;
	return m_vecPopulation;
}
