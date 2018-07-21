#pragma once
#include "../MSMcoreLib/Simulation.h"
#include <math.h>

class LamellarPhaseGenerator : public Simulation
{
private:
	Space *secondPhaseSpace;
	int numberOfGrains;
	constexpr double pi() { return atan(1) * 4; }
	
public:
	__declspec(dllexport) LamellarPhaseGenerator(Space *space);
	__declspec(dllexport) bool performStep() override;
	
};
