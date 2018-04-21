#pragma once
#include "NueralNet.h"
class CSweeper
{
private:
	CNueralNet m_nnBrain;
	double m_dFitness;
	double m_dRotation;
	double m_dScale;
	SVector2D m_svPos;
	vector<SPoint>m_vecSweeperVB;
	double m_dLTrack;
	double m_dRTrack;
	SVector2D m_svClosestMine;
	SVector2D m_svLookat;
	int m_iClosestMineIndex;

private:
	void Transform(vector<SPoint>& vbtmp);
	SVector2D& GetClosestMine(vector<CMine>& mine);
	BOOL CheckClosestMine(vector<CMine>&mine);
	
public:
	CSweeper(void);
	~CSweeper(void);
	void Rander(HDC surface);
	void Update(vector<CMine>& mine);
	void PutWeight(vector<double>w){m_nnBrain.PutWeight(w);}
	int GetWeightNum(){return m_nnBrain.GetweightNum();}
	vector<int> GetSplitPos(){return m_nnBrain.CaculateSplitPoit();}
	double GetFiteness(){return m_dFitness;}
	void Reset();
};

