#include "SphereCollision.h"
#include <math.h>


SphereCollision::SphereCollision() : v1(Velocity(0, 0, 0)), v2(Velocity(0, 0, 0)), u1(Velocity(0, 0, 0)), u2(Velocity(0, 0, 0))
{
}

void SphereCollision::resolve(Sphere* sphere, Sphere* otherSphere)
{
	determineAuxiliaryVelocitiesByRotatingForward(sphere, otherSphere);
	computeNewVelocitiesUsingOneDimNewtonian(sphere, otherSphere);
	sphere->setVelocity(determineFinalVelocityByRotatingBackward(&v1));
	otherSphere->setVelocity(determineFinalVelocityByRotatingBackward(&v2));
}

void SphereCollision::computeNewVelocitiesUsingOneDimNewtonian(Sphere* sphere, Sphere* otherSphere)
{
	double m1 = computeMass(sphere);
	double m2 = computeMass(otherSphere);
	v1 = Velocity(u1.getX() * (m1 - m2) / (m1 + m2) + u2.getX() * 2 * m2 / (m1 + m2), u1.getY(), u1.getZ());
	v2 = Velocity(u2.getX() * (m1 - m2) / (m1 + m2) + u1.getX() * 2 * m1 / (m1 + m2), u2.getY(), u2.getZ());
}

double SphereCollision::computeXYAngle(Coords* coords, Coords* otherCoords)
{
	double sphere1XPos = coords->getX();
	double sphere1YPos = coords->getY();
	double sphere2YPos = otherCoords->getY();
	double sphere2XPos = otherCoords->getX();
	return -atan2(sphere2YPos - sphere1YPos, sphere2XPos - sphere1XPos);
}

Velocity SphereCollision::rotateByXY(Velocity* velocity, double angle)
{
	double x = velocity->getX() * cos(angle) - velocity->getY() * sin(angle);
	double y = velocity->getX() * sin(angle) + velocity->getY() * cos(angle);
	return Velocity(x, y, velocity->getZ());
}

double SphereCollision::computeXZAngle(Coords* coords, Coords* otherCoords)
{
	double sphere1XPos = coords->getX();
	double sphere1ZPos = coords->getZ();
	double sphere2ZPos = otherCoords->getZ();
	double sphere2XPos = otherCoords->getX();
	return -atan2(sphere2ZPos - sphere1ZPos, sphere2XPos - sphere1XPos);
}

Velocity SphereCollision::rotateByXZ(Velocity* velocity, double angle)
{
	double x = velocity->getX() * cos(angle) - velocity->getZ() * sin(angle);
	double z = velocity->getX() * sin(angle) + velocity->getZ() * cos(angle);
	return Velocity(x, velocity->getY(), z);
}
