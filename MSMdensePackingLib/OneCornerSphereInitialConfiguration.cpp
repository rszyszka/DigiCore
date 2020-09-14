#include "OneCornerSphereInitialConfiguration.h"

OneCornerSphereInitialConfiguration::OneCornerSphereInitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator) : InitialConfiguration(bin, sphereGenerator)
{
}

void OneCornerSphereInitialConfiguration::init()
{
	addNewCircleInUpperLeftCorner();
}
