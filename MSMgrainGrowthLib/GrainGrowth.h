#pragma once
#include "../MSMcoreLib/Simulation.h"

class GrainGrowth : public Simulation 
{
protected:
	Space *nextStepSpace;
	int stepCounter;
	int progress;

	__declspec(dllexport) void updateSpace() const;
	__declspec(dllexport) Cell* getMostFrequentValue(Cell** cells) const;
public:
	__declspec(dllexport) GrainGrowth(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};