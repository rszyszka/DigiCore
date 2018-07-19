#pragma once
#include "../MSMcoreLib/Space.h"

class NucleonsGenerator
{
public:
	__declspec(dllexport) static void putNucleonsRandomly(Space* space, int nucleonsToInput);
};

