#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "Grain.h"

class Titanium : public Simulation
{
private:
	vector<Grain> grains;
	Space* spaceToRecover;
	Space* nextStepSpace;
	int stepCounter;
	int progress;

	void defineGrains();
	void updateSpace() const;
	Cell* getMostFrequentValue(Cell** cells, Cell** oldCells, int grainCellsId) const;
public:
	__declspec(dllexport) Titanium(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};
