#pragma once
#include "../MSMcoreLib/Simulation.h"
#include <math.h>
#include "Grain.h"

class LamellarPhaseGenerator : public Simulation
{
private:
	Space *secondPhaseSpace;
	int numberOfGrains;

	constexpr double pi() { return atan(1) * 4; }

	vector<Grain> grainsAngles;
	
public:
	__declspec(dllexport) LamellarPhaseGenerator(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) vector<Grain> getGrainsAngles();
	
};
