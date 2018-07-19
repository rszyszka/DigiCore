#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "../MSMcoreLib/UniquePointGenerator.h"

class McGrainGrowth : public Simulation
{
private:
	int noOfCells;
	int noOfMCS;
	int mcsCounter;
	double kT = 0.6;
	UniquePointGenerator *pointGen;
	random_device rd;

	int noOfQ;
	int progress;

	void putStates();

public:
	__declspec(dllexport) McGrainGrowth(Space *space, int noOfQ, int noOfMCS, double kT);
	__declspec(dllexport) McGrainGrowth(Space *space, int noOfMCS, double kT);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};