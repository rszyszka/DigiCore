#pragma once
#include "../MSMgrainGrowthLib/GrainGrowth.h"

class Titanium : public GrainGrowth
{
private:
	Space* spaceToRecover;
public:
	__declspec(dllexport) Titanium(Space *space);
	__declspec(dllexport) bool performStep() override;
};
