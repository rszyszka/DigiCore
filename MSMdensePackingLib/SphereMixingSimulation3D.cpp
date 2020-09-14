#include "SphereMixingSimulation3D.h"
#include "SphereCollision3D.h"
#include "GravityXZ.h"
#include "GravityYZ.h"
#include "GravityXY.h"

SphereMixingSimulation3D::SphereMixingSimulation3D(Space* space, Bin* bin) : SphereMixingSimulation(space, bin)
{
	collision = new SphereCollision3D();
    initializeGravitySequence();
}

void SphereMixingSimulation3D::initializeGravitySequence()
{
    Gravity* gravityXZ = new GravityXZ();
    Gravity* gravityYZ = new GravityYZ();
    Gravity* gravityXY = new GravityXY();
    gravityXZ->setNext(gravityYZ);
    gravityYZ->setNext(gravityXY);
    gravityXY->setNext(gravityXZ);

    gravity = gravityXZ;
}

void SphereMixingSimulation3D::updateSpherePosition(Sphere* sphere)
{
    updateSphereXPosition(sphere);
    updateSphereYPosition(sphere);
    updateSphereZPosition(sphere);
}

void SphereMixingSimulation3D::resolveCollisionsWithBoundaryPlanes(Sphere* sphere)
{
    resolveCollisionWithYZPlane(sphere);
    resolveCollisionWithXZPlane(sphere);
    resolveCollisionWithXYPlane(sphere);
}
