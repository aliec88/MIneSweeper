#include "StdAfx.h"
#include "Params.h"

//windows
int CParams::WindowWidth=400;

int CParams::WindowHeight=400;

double CParams::FPS=0;

int CParams::TickNumber=0;

double CParams::PI=3.14159265358979;

//neuralnet
int CParams::InputNumbers=0;

int CParams::OutputNumbers=0;

int CParams::HiddenLayersNumbers=0;

int CParams::NeuronPerLayers=0;

int CParams::ActivationResponse=0;

//ga
double CParams::MaxPerturbation=0;

double CParams::NumberElitism=0;

int CParams::PopulationNumber=0;

double CParams::CrossoverRate=0;

double CParams::MutationRate=0;

//object

int CParams::NumberMines=0;

double CParams::MineScale=0;

double CParams::SweeperScale=0;

double CParams::MaxRotation=0;

bool CParams::LoadParams(char* szFilename)
{
	ifstream ifile(szFilename);
	if (!ifile)
	{
		return false;
	}
	char ParamDescription[40]={0};
	ifile>>ParamDescription;
	ifile>>FPS;

	ifile>>ParamDescription;
	ifile>>TickNumber;

	ifile>>ParamDescription;
	ifile>>InputNumbers;

	ifile>>ParamDescription;
	ifile>>OutputNumbers;

	ifile>>ParamDescription;
	ifile>>HiddenLayersNumbers;

	ifile>>ParamDescription;
	ifile>>NeuronPerLayers;

	ifile>>ParamDescription;
	ifile>>ActivationResponse;

	ifile>>ParamDescription;
	ifile>>MaxPerturbation;

	ifile>>ParamDescription;
	ifile>>NumberElitism;

	ifile>>ParamDescription;
	ifile>>PopulationNumber;

	ifile>>ParamDescription;
	ifile>>CrossoverRate;

	ifile>>ParamDescription;
	ifile>>MutationRate;

	ifile>>ParamDescription;
	ifile>>NumberMines;

	ifile>>ParamDescription;
	ifile>>MineScale;

	ifile>>ParamDescription;
	ifile>>SweeperScale;

	ifile>>ParamDescription;
	ifile>>MaxRotation;
	
	return true;
}

CParams::CParams(void)
{
	if (!LoadParams("params.ini"))
	{
		MessageBox(0,TEXT("不能找到params.ini文件"),TEXT("初始化失败"),0);
	}
}


CParams::~CParams(void)
{
}
