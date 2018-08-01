#pragma once
#include "stdafx.h"
#include <random>
#include "Simulation.h"
#include "LamellarPhaseGenerator.h"
#include "Space.h"

class Controller
{
private:
	Space * space;
	Simulation * grainGrowth;
	LamellarPhaseGenerator* lamellarPhaseAddition;
	random_device rd;

public:
	~Controller();
	Controller();
	void StartProcess();
	void PrepareProcess(int* argc, char** argv[]);
	void CloseProcess();
};
