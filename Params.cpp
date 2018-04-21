#include "StdAfx.h"
#include "Params.h"


BOOL CParams::LoadParamFile(char* filename)
{
	fstream load(filename);
	if (load==FALSE)
	{
		return FALSE;
	}
	char ParamDescription[40];
	load>>ParamDescription;
	load>>WindowWidth;
	load>>ParamDescription;
	load>>WindowHeight;
	load>>ParamDescription;
	load>>FPS ;
	load>>ParamDescription;
	load>>MineNumber;
	load>>ParamDescription;
	load>>SweeperNumber;
	load>>ParamDescription;
	load>>TickNumber;
	load>>ParamDescription;
	load>>MineScale;
	load>>ParamDescription;
	load>>SweeperScale ;
	load>>ParamDescription;
	load>>MaxSpeed;
	load>>ParamDescription;
	load>>Population;
	load>>ParamDescription;
	load>>ElitismNumber;
	load>>ParamDescription;
	load>>CrossoverRate;
	load>>ParamDescription;
	load>>MutateRate;
	load>>ParamDescription;
	load>>MaxPerturbation ;
	load>>ParamDescription;
	load>>NumInputs;
	load>>ParamDescription;
	load>>NumHiddenLayers;
	load>>ParamDescription;
	load>>NumNeuronPerLayers;
	load>>ParamDescription;
	load>>NumOutputs;
	return TRUE;
}

CParams::CParams(void)
{
	if (!LoadParamFile("param.ini"))
	{
		MessageBox(NULL,TEXT("º”‘ÿ≈‰÷√Œƒº˛ ß∞‹"),TEXT(" ß∞‹"),0);
	}
}


CParams::~CParams(void)
{
}

double CParams::PI=3.14159265358979;

int CParams::WindowWidth=0;

int CParams::WindowHeight=0;

int CParams::FPS=0;

int CParams::MineNumber=0;

int CParams::SweeperNumber=0;

int CParams::TickNumber=0;

int CParams::MineScale=0;

int CParams::SweeperScale=0;

double CParams::MaxSpeed=0;

int CParams::Population=0;

int CParams::ElitismNumber=0;

double CParams::CrossoverRate=0;

double CParams::MutateRate=0;

double CParams::MaxPerturbation=0;

int CParams::NumInputs=0;

int CParams::NumHiddenLayers=0;

int CParams::NumNeuronPerLayers=0;

int CParams::NumOutputs=0;
