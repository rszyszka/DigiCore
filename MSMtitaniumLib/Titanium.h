#pragma once
#include "../MSMcoreLib/NucleonsGenerator.h"
#include "../MSMgrainGrowthLib/GrainGrowth.h"
#include "../MSMlamellarPhaseGeneratorLib/LamellarPhaseGenerator.h"
#include "../MSMcircullarInclusionsGeneratorLib/CircullarInclusionsAddition.h"

#include "Grain.h"

class Titanium : public Simulation
{
private:

	Simulation * lamellarPhaseAddition;
	Simulation * circullarInclusionsAddition;

	int twinWidth;
	int inclusionMaxRadius, inclusionsCoverage;
	int betaPhaseNucleonsToPut;

	vector<Grain> grains;
	Space* spaceToRecover;
	Space* nextStepSpace;
	int stepCounter;
	int progress;

	void initializeGrains();
	void growBetaPhaseGrains();
	void recoverSpace();
	void setSpaceToRecover(Space*);
	void setNextStepSpace(Space*);
	void updateSpace() const;
	Cell* getMostFrequentValue(Cell** cells, Cell** oldCells, int grainCellsId) const;
public:
	__declspec(dllexport) Titanium(Space *space);
	__declspec(dllexport) Titanium(Space *space, int twinWidth, int inclusionMaxRadius, int inclusionsCoverage, int betaPhaseNucleonsToPut);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
};