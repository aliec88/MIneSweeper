#pragma once
class CParams
{
public:
	static int WindowWidth;
	static int WindowHeight;
	static double FPS;
	static int TickNumber;
	static double PI;
public:
	static int InputNumbers;
	static int OutputNumbers;
	static int HiddenLayersNumbers;
	static int NeuronPerLayers;
	static int ActivationResponse;
public:
	static double MaxPerturbation;
	static double NumberElitism;
	static int PopulationNumber;
	static double CrossoverRate;
	static double MutationRate;
public:
	static int NumberMines;
	static double MineScale;
	static double SweeperScale;
	static double MaxRotation;
private:
	bool LoadParams(char* szFilename);
public:
	CParams(void);
	~CParams(void);
};

