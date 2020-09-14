#include "SphereCollision2D.h"
#include <math.h>


void SphereCollision2D::determineAuxiliaryVelocitiesByRotatingForward(Sphere* sphere, Sphere* otherSphere)
{
	angle = computeXYAngle(sphere->getCoords(), otherSphere->getCoords());
	u1 = rotateByXY(sphere->getVelocity(), angle);
	u2 = rotateByXY(otherSphere->getVelocity(), angle);
}

Velocity SphereCollision2D::determineFinalVelocityByRotatingBackward(Velocity* v)
{
	return rotateByXY(v, -angle);
}

double SphereCollision2D::computeMass(Sphere* sphere)
{
	return PI * pow(sphere->getR(), 2);
}
