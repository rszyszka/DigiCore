#pragma once
#include "AbstractSphereGenerator.h"
class RandomSphereGenerator : public AbstractSphereGenerator
{
public:
	__declspec(dllexport) RandomSphereGenerator(int minRadius, int maxRadius);
	__declspec(dllexport) Sphere* generateNewSphere() override;
};

