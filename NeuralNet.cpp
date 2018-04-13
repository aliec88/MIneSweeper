#include "StdAfx.h"
#include "NeuralNet.h"


void CNeuralNet::CreateNet()
{
	if (m_iHiddenLayersNumbers>0)
	{
		m_vecNet.push_back(SNeuronLayer(m_iNeuronPerLayers,m_iInputNumbers));
		for (int i=0;i<m_iHiddenLayersNumbers-1;i++)
		{
			m_vecNet.push_back(SNeuronLayer(m_iNeuronPerLayers,m_iNeuronPerLayers));
		}
		m_vecNet.push_back(SNeuronLayer(m_iOutputNumbers,m_iNeuronPerLayers));
	}else
	{
		m_vecNet.push_back(SNeuronLayer(m_iOutputNumbers,m_iInputNumbers));
	}
	
}

CNeuralNet::CNeuralNet(void)
{
	m_iInputNumbers=CParams::InputNumbers;
	m_iOutputNumbers=CParams::OutputNumbers;
	m_iHiddenLayersNumbers=CParams::HiddenLayersNumbers;
	m_iNeuronPerLayers=CParams::NeuronPerLayers;
	CreateNet();
}


CNeuralNet::~CNeuralNet(void)
{
}

void CNeuralNet::PutWeights(vector<double>& weights)
{
	int pos=0;
	for (int i=0;i<m_iHiddenLayersNumbers+1;i++)
	{
		for(int j=0;j<m_vecNet[i].m_iNeuronNumbers;j++)
		{
			for (int k=0;k<m_vecNet[i].m_vecNeurons[j].m_iInputNumbers;k++)
			{
				m_vecNet[i].m_vecNeurons[j].m_vecWeight[k]=weights[pos++];
			}
		}
	}
}

vector<double> CNeuralNet::Update(vector<double>& input)
{
	vector<double>outputs;
	int pos=0;
	if (m_iInputNumbers!=input.size())
	{
		return outputs;
	}
	for (int i=0;i<m_iHiddenLayersNumbers+1;i++)
	{
		if (i>0)
		{
			input=outputs;
		}
		outputs.clear();
		pos=0;
		for (int j=0;j<m_vecNet[i].m_iNeuronNumbers;j++)
		{
			double netinput=0;
			int numinput=m_vecNet[i].m_vecNeurons[j].m_iInputNumbers-1;
			for (int k=0;k<numinput;k++)
			{
				netinput+=m_vecNet[i].m_vecNeurons[j].m_vecWeight[k]*input[pos++];
			}
			netinput-=m_vecNet[i].m_vecNeurons[j].m_vecWeight[numinput];
			outputs.push_back(Sigmoid(netinput,CParams::ActivationResponse));
			pos=0;

		}
	}
	return outputs;
}

vector<double> CNeuralNet::GetWeight() const
{
	vector<double>weight;
	for (int i=0;i<m_iHiddenLayersNumbers+1;i++)
	{
		for (int j=0;i<m_vecNet[i].m_iNeuronNumbers;j++)
		{
			for (int k=0;k<m_vecNet[i].m_vecNeurons[j].m_iInputNumbers;k++)
			{
				weight.push_back(m_vecNet[i].m_vecNeurons[j].m_vecWeight[k]);
			}
		}
	}
	return weight;
}

int CNeuralNet::GetNumberOfWeight() const
{
	int num=0;
	for (int i=0;i<m_iHiddenLayersNumbers+1;i++)
	{
		for (int j=0;j<m_vecNet[i].m_iNeuronNumbers;j++)
		{
			for (int k=0;k<m_vecNet[i].m_vecNeurons[j].m_iInputNumbers;k++)
			{
				num++;
			}
		}
	}
	return num;
}

SNeuron::SNeuron(int input):m_iInputNumbers(input+1)
{
	for (int i=0;i<input+1;i++)
	{
		m_vecWeight.push_back(0);
	}
}

SNeuronLayer::SNeuronLayer(int neuron,int inputperneuron):m_iNeuronNumbers(neuron)
{
	for (int i=0;i<neuron;i++)
	{
		m_vecNeurons.push_back(SNeuron(inputperneuron));
	}
}
