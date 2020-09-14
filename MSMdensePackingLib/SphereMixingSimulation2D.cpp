#include "SphereMixingSimulation2D.h"
#include "SphereCollision2D.h"
#include "GravityXZ.h"
#include "GravityYZ.h"

SphereMixingSimulation2D::SphereMixingSimulation2D(Space* space, Bin* bin) : SphereMixingSimulation(space, bin)
{
	collision = new SphereCollision2D();
    initializeGravitySequence();
}

void SphereMixingSimulation2D::initializeGravitySequence()
{
    Gravity* gravityXZ = new GravityXZ();
    Gravity* gravityYZ = new GravityYZ();
    gravityXZ->setNext(gravityYZ);
    gravityYZ->setNext(gravityXZ);

    gravity = gravityXZ;
}

void SphereMixingSimulation2D::updateSpherePosition(Sphere* sphere)
{
    updateSphereXPosition(sphere);
    updateSphereYPosition(sphere);
}

void SphereMixingSimulation2D::resolveCollisionsWithBoundaryPlanes(Sphere* sphere)
{
    resolveCollisionWithYZPlane(sphere);
    resolveCollisionWithXZPlane(sphere);
}
