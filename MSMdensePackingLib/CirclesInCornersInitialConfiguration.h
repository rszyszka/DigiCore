#pragma once
#include "InitialConfiguration.h"

class CirclesInCornersInitialConfiguration : public InitialConfiguration
{
public:
	CirclesInCornersInitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator);
	void init() override;

private:
	void addNewCircleInLowerLeftCorner();
};
