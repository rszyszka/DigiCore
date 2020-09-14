#pragma once
#include "stdafx.h"
#include <random>
#include "Simulation.h"
#include "LamellarPhaseGenerator.h"
#include "CircullarInclusionsAddition.h"
#include "Titanium.h"
#include "Space.h"
#include "Bin.h"

class Controller
{
private:
	Bin* bin;
	Space* space;
	Simulation* simulation;
	random_device rd;

public:
	~Controller();
	Controller();
	void StartProcess();
	void PrepareProcess(int* argc, char** argv[]);
	void CloseProcess();
};
