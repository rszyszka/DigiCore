#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "GreedyPackingSimulation.h"
#include "SphereMixingSimulation.h"

class DensePackingSimulation : public Simulation
{

public:
	__declspec(dllexport) DensePackingSimulation(Space* space, int minR, int maxR);
	bool performStep() override;
	int getProgress() override;
	Bin* getBin();

private:
	Bin* bin;
	GreedyPackingSimulation* greedyPackingSimulation;
	SphereMixingSimulation* mixingSpheresSimulation;
	int minR;
	int maxR;
	int numberOfFilledCells;

	void performGreedyPacking();
	double computeVoxelDensityLevel();
};

