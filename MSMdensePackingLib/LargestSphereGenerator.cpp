#include "LargestSphereGenerator.h"

LargestSphereGenerator::LargestSphereGenerator(int minRadius, int maxRadius) : AbstractSphereGenerator(minRadius, maxRadius)
{
}

Sphere* LargestSphereGenerator::generateNewSphere()
{
	return new Sphere(maxRadius);
}
