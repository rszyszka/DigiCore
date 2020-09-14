#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "GreedyPacker.h"

class GreedyPackingSimulation : public Simulation
{
public:
	const double PI = 3.14159265358979323846;

	__declspec(dllexport) GreedyPackingSimulation(Space* space, GreedyPacker* packer);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
	__declspec(dllexport) double computeMathDensityLevel();

private:
	Bin* bin;
	GreedyPacker* packer;

	double computeMathSpheresDensityLevel();
	double computeMathCircleDensityLevel();
};

