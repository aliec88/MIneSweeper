#pragma once
struct SNeuron
{
	int m_iNumInputs;
	vector<double>m_vecWeight;
	SNeuron(int inputnum);
};
struct SNeuronLayer
{
	int m_iNumNeuronPerLayer;
	vector<SNeuron>m_vecNeuronLayer;
	SNeuronLayer(int numNerronPerLayer,int numInputsPerNeuron);
};
class CNueralNet
{
private:
	int m_iNumInputs;
	int m_iNumOutputs;
	int m_iNumHiddenLayers;
	int m_iNumNeuronPerLayers;
	vector<SNeuronLayer>m_vecNueralNet;
public:
	CNueralNet(void);
	~CNueralNet(void);
	void PutWeight(vector<double>weight);
	int GetweightNum();
	vector<double> Update(vector<double>&input);
	vector<int> CaculateSplitPoit();
};

