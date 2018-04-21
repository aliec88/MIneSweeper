#include "StdAfx.h"
#include "NueralNet.h"


CNueralNet::CNueralNet(void)
{
	m_iNumInputs=CParams::NumInputs;
	m_iNumHiddenLayers=CParams::NumHiddenLayers;
	m_iNumNeuronPerLayers=CParams::NumNeuronPerLayers;
	m_iNumOutputs=CParams::NumOutputs;
	if (m_iNumHiddenLayers<=0)
	{
		m_vecNueralNet.push_back(SNeuronLayer(m_iNumOutputs,m_iNumInputs));
	}else
	{
		int tempinput=m_iNumInputs;
		for (int i=0;i<m_iNumHiddenLayers;i++)
		{
			m_vecNueralNet.push_back(SNeuronLayer(m_iNumNeuronPerLayers,tempinput));
			tempinput=m_iNumNeuronPerLayers;
		}
		m_vecNueralNet.push_back(SNeuronLayer(m_iNumOutputs,tempinput));

	}
	
}


CNueralNet::~CNueralNet(void)
{
}

void CNueralNet::PutWeight(vector<double>weight)
{
	int pos=0;
	for (int i=0;i<m_iNumHiddenLayers+1;i++)
	{
		for (int j=0;j<m_vecNueralNet[i].m_iNumNeuronPerLayer;j++)
		{
			for (int k=0;k<m_vecNueralNet[i].m_vecNeuronLayer[j].m_iNumInputs;k++)
			{
				m_vecNueralNet[i].m_vecNeuronLayer[j].m_vecWeight[k]=weight[pos++];
			}
		}
	}
}

int CNueralNet::GetweightNum()
{
	int pos=0;
	for (int i=0;i<m_iNumHiddenLayers+1;i++)
	{
		for (int j=0;j<m_vecNueralNet[i].m_iNumNeuronPerLayer;j++)
		{
			for (int k=0;k<m_vecNueralNet[i].m_vecNeuronLayer[j].m_iNumInputs;k++)
			{
				pos++;
			}
		}
	}
	return pos;
}

vector<double> CNueralNet::Update(vector<double>&input)
{
	int pos=0;
	double result=0;
	vector<double>output;
	for (int i=0;i<m_iNumHiddenLayers+1;i++)
	{
		if (i>0)
		{
			input=output;
		}
		output.clear();
		pos=0;
		for (int j=0;j<m_vecNueralNet[i].m_iNumNeuronPerLayer;j++)
		{
			int inputnumber=m_vecNueralNet[i].m_vecNeuronLayer[j].m_iNumInputs-1;
			for (int k=0;k<inputnumber;k++)
			{
				result+=m_vecNueralNet[i].m_vecNeuronLayer[j].m_vecWeight[k]*input[pos++];
			}
			result-=m_vecNueralNet[i].m_vecNeuronLayer[j].m_vecWeight[inputnumber];
			output.push_back(Sigmoid(result,1));
			pos=0;
		}
	}
	return output;
}

vector<int> CNueralNet::CaculateSplitPoit()
{
	vector<int>point;
	int pos=0;
	for (int i=0;i<m_iNumHiddenLayers+1;i++)
	{
		for (int j=0;j<m_vecNueralNet[i].m_iNumNeuronPerLayer;j++)
		{
			for (int k=0;k<m_vecNueralNet[i].m_vecNeuronLayer[j].m_iNumInputs;k++)
			{
				pos++;
			}
			point.push_back(pos-1);
		}
	}
	return point;
}

SNeuron::SNeuron(int inputnum):m_iNumInputs(inputnum+1)
{
	for (int i=0;i<inputnum+1;i++)
	{
		m_vecWeight.push_back(0);
	}
}

SNeuronLayer::SNeuronLayer(int numNerronPerLayer,int numInputsPerNeuron):m_iNumNeuronPerLayer(numNerronPerLayer)
{
	for (int i=0;i<numNerronPerLayer;i++)
	{
		m_vecNeuronLayer.push_back(SNeuron(numInputsPerNeuron));
	}
}
