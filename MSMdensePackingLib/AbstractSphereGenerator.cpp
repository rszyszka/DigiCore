#include "AbstractSphereGenerator.h"

AbstractSphereGenerator::AbstractSphereGenerator(int minRadius, int maxRadius) : minRadius(minRadius)
{
	this->maxRadius = maxRadius;
	this->originMaxRadius = maxRadius;
}

bool AbstractSphereGenerator::setLowerRadiusIfPossible(int currentCircleRadius)
{
    if (currentCircleRadius <= minRadius) {
        return false;
    }
    maxRadius = currentCircleRadius - 1;
    return true;
}

void AbstractSphereGenerator::resetMaxRadius()
{
    maxRadius = originMaxRadius;
}
