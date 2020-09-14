#pragma once
#include "AbstractSphereGenerator.h"

class LargestSphereGenerator : public AbstractSphereGenerator
{
public:
	LargestSphereGenerator(int minRadius, int maxRadius);
	Sphere* generateNewSphere() override;
};

