#pragma once
struct SChromosome
{
	double m_dFitness;
	vector<double>m_vecGenBit;
	SChromosome(){m_dFitness=0;}
	SChromosome(vector<double>w,double fitness){m_vecGenBit=w;m_dFitness=fitness;}
	bool operator<(const SChromosome& r)
	{
		return this->m_dFitness<r.m_dFitness;
	}
};
class CGA
{
private:
	int m_iPopNum;
	int m_iChromLenght;
	double m_dTotalFitness;
	double m_dBestFitness;
	double m_dWorstFitness;
	double m_dAverageFitness;
	double m_dCrossoverRate;
	double m_dMutationRate;
	vector<SChromosome>m_vecPopulation;
private:
	void CreatePopulation();
	void Best(int num,vector<SChromosome>&newPop);
	SChromosome RoultteSelect();
	void Crossover(const vector<double>&dad,const vector<double>&mum,vector<double>&baby1,vector<double>&baby2);
	void Mutate(vector<double>& chrom);
	void CaculateFitness();
	vector<SChromosome>Epoch(vector<SChromosome>& OldPopulation);
public:
	CGA(double chromlength);
	~CGA(void);
	vector<SChromosome>Update(vector<SChromosome>& Popcopy);
	vector<SChromosome>GetPopulation(){return m_vecPopulation;}
	void SetPopulation(vector<SChromosome>pop){m_vecPopulation=pop;}
	double GetBestFitness(){return m_dBestFitness;}
	double GetAverFitness(){return m_dAverageFitness;}
};

