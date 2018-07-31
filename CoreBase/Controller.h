#pragma once
#include "stdafx.h"
#include <random>
#include "Simulation.h"
#include "Space.h"

class Controller
{
private:
	Space * space;
	Simulation * grainGrowth;
	Simulation * lamellarPhaseAddition;
	random_device rd;

public:
	~Controller();
	Controller();
	void StartProcess();
	void PrepareProcess(int* argc, char** argv[]);
	void CloseProcess();
};
