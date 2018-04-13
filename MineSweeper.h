#pragma once
#include "Mine.h"
class CMineSweeper
{
private:
	CNeuralNet m_nnBrain;
	SVector2D m_svPosition;
	SVector2D m_svLookAt;
	SVector2D m_svClosestMinePos;
	double m_dRotation;
	double m_dSpeed;
	double m_lTrack,m_rTrack;
	double m_dFitness;
	double m_dScale;
	int m_iClosestMine;
	HPEN m_hOldPen;
	vector<SPoint>m_vecSweeperVertexs;
	vector<double>m_vecInput;
	vector<double>m_vecOutput;
private:
	void Transform(vector<SPoint>& ver,SVector2D& pos,double scale,double rotate);
	void GetClosestMine(vector<CMine>& mine);
	BOOL CheckForMine(vector<CMine>& mine);
public:
	CMineSweeper(void);
	~CMineSweeper(void);
	void Update(vector<CMine>& mine);
	void Rander(HDC surface,HPEN pen);
	void Reset();
	CNeuralNet GetBrain(){return m_nnBrain;}
	double GetFitness(){return m_dFitness;}
	void PutWeights(vector<double>weight){m_nnBrain.PutWeights(weight);}
	int GetWeightNum(){return m_nnBrain.GetNumberOfWeight();}
};

