#pragma once
#include "HolesFinder.h"
#include "InitialConfiguration.h"

class GreedyPacker
{
public:
	__declspec(dllexport) GreedyPacker(InitialConfiguration* initialConfiguration, HolesFinder* holesFinder);
	void createInitialConfiguration();
	Bin* getBin();
	bool tryToPackNextCircle();

private:
	InitialConfiguration* initialConfiguration;
	Bin* bin;
	SphereGenerator* sphereGenerator;
	HolesFinder* holesFinder;

	bool tryToGenerateAndPackNewSphereWithDiminishedRadius(Sphere* sphere);
};
