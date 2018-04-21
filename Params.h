#pragma once
class CParams
{
private:
	BOOL LoadParamFile(char* filename);
public:
	CParams(void);
	~CParams(void);
public:
	//main
	static double PI;
	static int WindowWidth;
	static int WindowHeight;
	static int FPS;
    //controller
	static int MineNumber;
	static int SweeperNumber;
	static int TickNumber;
	//mine and sweeper
	static int MineScale;
	static int SweeperScale;
	static double MaxSpeed;
	//GA
	static int Population;
	static int ElitismNumber;
	static double CrossoverRate;
	static double MutateRate;
	static double MaxPerturbation;
	//neuron
	static int NumInputs;
	static int NumHiddenLayers;
	static int NumNeuronPerLayers;
	static int NumOutputs;
};

