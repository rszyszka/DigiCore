#pragma once
#include "InitialConfiguration.h"

class TangentialCirclesInitialConfiguration : public InitialConfiguration
{
public:
	__declspec(dllexport) TangentialCirclesInitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator);
	void init() override;

private:
	void addNewCircleNextToFirstOne();
};

