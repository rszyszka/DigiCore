#pragma once
#include "InitialConfiguration.h"

class OneCornerSphereInitialConfiguration : public InitialConfiguration
{
public:
	OneCornerSphereInitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator);
	void init() override;
};

