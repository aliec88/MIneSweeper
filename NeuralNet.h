#pragma once
struct SNeuron
{
	int m_iInputNumbers;
	vector<double>m_vecWeight;
	SNeuron(int input);
};
struct SNeuronLayer
{
	int m_iNeuronNumbers;
	vector<SNeuron>m_vecNeurons;
	SNeuronLayer(int neuron,int inputperneuron);
};
class CNeuralNet
{
private:
	int m_iInputNumbers;
	int m_iOutputNumbers;
	int m_iHiddenLayersNumbers;
	int m_iNeuronPerLayers;
	vector<SNeuronLayer>m_vecNet;
private:
	void CreateNet();
public:
	inline double Sigmoid(double activation,double response){return 1/(1+exp(-activation/response));}
public:
	CNeuralNet(void);
	~CNeuralNet(void);
	void PutWeights(vector<double>& weights);
	vector<double> Update(vector<double>& input);
	vector<double>GetWeight() const;
	int GetNumberOfWeight()const;
};

