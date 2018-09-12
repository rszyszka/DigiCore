#pragma once
#include "stdafx.h"
#include <random>
#include "Simulation.h"
#include "LamellarPhaseGenerator.h"
#include "CircullarInclusionsAddition.h"
#include "Space.h"

class Controller
{
private:
	Space * space;
	Simulation * grainGrowth;
	Simulation * lamellarPhaseAddition;
	Simulation * circullarInclusionsAddition;
	random_device rd;

public:
	~Controller();
	Controller();
	void StartProcess();
	void PrepareProcess(int* argc, char** argv[]);
	void CloseProcess();
};
