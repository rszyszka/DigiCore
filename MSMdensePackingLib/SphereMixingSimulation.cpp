#include "SphereMixingSimulation.h"
#include "SphereMixingSimulation2D.h"
#include "SphereMixingSimulation3D.h"
#include "Utils.h"

void SphereMixingSimulation::stop()
{
	mixing = false;
}

void SphereMixingSimulation::changeGravityStateAndResetSpheresVelocities()
{
	gravity = gravity->changeState();
	for (Sphere* sphere : bin->getSpheres()) {
		sphere->setVelocity(Velocity((randomDouble() - 0.5), (randomDouble() - 0.5), (randomDouble() - 0.5)));
	}
}

bool SphereMixingSimulation::performStep()
{
	setMixing(true); // one should setMixing(false) from separate thread to stop simulation
	for (Sphere* sphere : bin->getSpheres()) {
		backupSpherePosition(sphere);
		updateSpherePosition(sphere);
		resolveCollisionsWithOtherSpheres(sphere);
		resolveCollisionsWithBoundaryPlanes(sphere);
		revertSpherePositionIfItIsOverlappingOtherSpheres(sphere);
		gravity->applyToSphereVelocity(sphere);
	}
	return isMixing();
}

int SphereMixingSimulation::getProgress()
{
	return 0; //TODO
}

bool SphereMixingSimulation::isMixing()
{
	return false;
}

void SphereMixingSimulation::setMixing(bool mixing)
{
	this->mixing = mixing;
}

SphereMixingSimulation* SphereMixingSimulation::create(Space* space, Bin* bin)
{
	if (bin->getZSize() == 1) {
		return new SphereMixingSimulation2D(space, bin);
	}
	else {
		return new SphereMixingSimulation3D(space, bin);
	}
}

SphereMixingSimulation::SphereMixingSimulation(Space* space, Bin* bin) : Simulation(space)
{
	currentSphereXPos = 0.0;
	currentSphereYPos = 0.0;
	currentSphereZPos = 0.0;
	this->collision = nullptr;
	this->gravity = nullptr;
	this->mixing = true;
	this->bin = bin;
}

void SphereMixingSimulation::updateSphereXPosition(Sphere* sphere)
{
	sphere->getCoords()->setX(currentSphereXPos + sphere->getVelocity()->getX());
}

void SphereMixingSimulation::updateSphereYPosition(Sphere* sphere)
{
	sphere->getCoords()->setY(currentSphereYPos + sphere->getVelocity()->getY());
}

void SphereMixingSimulation::updateSphereZPosition(Sphere* sphere)
{
	sphere->getCoords()->setZ(currentSphereZPos + sphere->getVelocity()->getZ());
}

void SphereMixingSimulation::resolveCollisionWithYZPlane(Sphere* sphere)
{
	if (isOverlappingSize(sphere->getCoords()->getX(), sphere->getR(), bin->getXSize())) {
		sphere->getVelocity()->negateX();
		updateSphereXPosition(sphere);
	}
}


void SphereMixingSimulation::resolveCollisionWithXZPlane(Sphere* sphere)
{
	if (isOverlappingSize(sphere->getCoords()->getY(), sphere->getR(), bin->getYSize())) {
		sphere->getVelocity()->negateY();
		updateSphereYPosition(sphere);
	}
}

void SphereMixingSimulation::resolveCollisionWithXYPlane(Sphere* sphere)
{
	if (isOverlappingSize(sphere->getCoords()->getZ(), sphere->getR(), bin->getZSize())) {
		sphere->getVelocity()->negateZ();
		updateSphereZPosition(sphere);
	}
}

void SphereMixingSimulation::backupSpherePosition(Sphere* sphere)
{
	currentSphereXPos = sphere->getCoords()->getX();
	currentSphereYPos = sphere->getCoords()->getY();
	currentSphereZPos = sphere->getCoords()->getZ();
}

void SphereMixingSimulation::resolveCollisionsWithOtherSpheres(Sphere* sphere)
{
	for (Sphere* otherSphere : bin->getSpheres()) {
		if (sphere == otherSphere) {
			continue;
		}
		if (areSpheresOverlapping(sphere, otherSphere)) {
			resolveSpheresCollision(sphere, otherSphere);
			updateSpherePosition(sphere);
		}
	}
}

void SphereMixingSimulation::resolveSpheresCollision(Sphere* sphere, Sphere* otherSphere)
{
	collision->resolve(sphere, otherSphere);
}

void SphereMixingSimulation::revertSpherePositionIfItIsOverlappingOtherSpheres(Sphere* sphere)
{
	if (isSphereOverlappingAnyOtherSphereInBin(sphere, bin)) {
		sphere->getCoords()->setX(currentSphereXPos);
		sphere->getCoords()->setY(currentSphereYPos);
		sphere->getCoords()->setZ(currentSphereZPos);
	}
}
