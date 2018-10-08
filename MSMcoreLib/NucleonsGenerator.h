#pragma once
#include "../MSMcoreLib/Space.h"

class NucleonsGenerator
{
public:
	__declspec(dllexport) static void putNucleonsRandomly(Space* space, int nucleonsToInput);
	__declspec(dllexport) static void putNucleonsOfBetaPhaseRandomly(Space* space, int nucleonsToInput);
	__declspec(dllexport) static void putNucleonsOfBetaPhaseRandomly(Space* space, int nucleonsToInput, vector<Point*> grainPoints);
};

