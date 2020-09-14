#include "CirclesInCornersInitialConfiguration.h"

CirclesInCornersInitialConfiguration::CirclesInCornersInitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator) : InitialConfiguration(bin,sphereGenerator)
{
}

void CirclesInCornersInitialConfiguration::init()
{
	addNewCircleInUpperLeftCorner();
	addNewCircleInLowerLeftCorner();
}

void CirclesInCornersInitialConfiguration::addNewCircleInLowerLeftCorner()
{
	Sphere* sphere = sphereGenerator->generateNewSphere();
	Coords* coords = bin->getZSize() == 1 ? Coords::coords(sphere->getR(), sphere->getR()) : Coords::coords(sphere->getR(), sphere->getR(), sphere->getR());
	sphere->setCoords(*coords);
	bin->addSphere(sphere);
	delete coords;
}
