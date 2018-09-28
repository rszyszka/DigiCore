#pragma once
#include "../MSMcoreLib/Simulation.h"

class Titanium : public Simulation
{
private:
	Space* spaceToRecover;
	Space* nextStepSpace;
	int stepCounter;
	int progress;

	void updateSpace() const;
	Cell* getMostFrequentValue(Cell** cells) const;
public:
	__declspec(dllexport) Titanium(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};
