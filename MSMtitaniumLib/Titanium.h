#pragma once
#include "../MSMcoreLib/NucleonsGenerator.h"
#include "../MSMgrainGrowthLib/GrainGrowth.h"
#include "../MSMlamellarPhaseGeneratorLib/LamellarPhaseGenerator.h"
#include "../MSMcircullarInclusionsGeneratorLib/CircullarInclusionsAddition.h"

#include "Grain.h"

class Titanium : public Simulation
{
private:

	Simulation * grainGrowth;
	Simulation * lamellarPhaseAddition;
	Simulation * circullarInclusionsAddition;

	vector<Grain> grains;
	Space* spaceToRecover;
	Space* nextStepSpace;
	int stepCounter;
	int progress;

	void defineGrains();
	void growBetaPhaseGrains();
	void setSpaceToRecover(Space*);
	void setNextStepSpace(Space*);
	void updateSpace() const;
	Cell* getMostFrequentValue(Cell** cells, Cell** oldCells, int grainCellsId) const;
public:
	__declspec(dllexport) Titanium(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};
