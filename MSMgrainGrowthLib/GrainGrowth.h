#pragma once
#include "../MSMcoreLib/Simulation.h"

class GrainGrowth : public Simulation 
{
private:
	Space *nextStepSpace;
	int stepCounter;
	int progress;

	void updateSpace() const;
	Cell* getMostFrequentValue(Cell** cells) const;
public:
	__declspec(dllexport) GrainGrowth(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};