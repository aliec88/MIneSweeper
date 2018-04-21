#pragma once
struct SChromsome
{
	double m_dFitness;
	vector<double>m_vecGenBit;
	SChromsome(){m_dFitness=0;}
	SChromsome(int genlength);
	BOOL operator<(SChromsome& right)
	{
		return this->m_dFitness<right.m_dFitness;
	}
};
class CGA
{
private:
	vector<SChromsome>m_vecPopulation;
	int m_iGenLenght;
	double m_dBestFitness;
	double m_dAverageFitness;
	double m_dTotalFitness;
	vector<int>m_vecSplitPos;
private:
	void CaculateFitness();
	void GrabBest(vector<SChromsome>& newpop,int num);
	SChromsome RouletteSelect();
	void Crossover(const vector<double>& mum,const vector<double>& dad,vector<double>&baby1,vector<double>&baby2);
	void Mutate(vector<double>& chromgenbit);
	void Epoch(vector<SChromsome>& oldpop);
	void Reset();

public:
	CGA(){}
	CGA(int genlength,vector<int>&splitPos);
	~CGA(void);
	vector<SChromsome>GetPopulation(){return m_vecPopulation;}
	vector<SChromsome>& Update(vector<SChromsome>& oldpop);
	double GetBestFitness(){return m_dBestFitness;}
	double GetAverFitness(){return m_dAverageFitness;}
};

