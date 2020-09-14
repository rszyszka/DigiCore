#pragma once
#include "Bin.h"
#include "Gravity.h"
#include "SphereCollision.h"
#include "../MSMcoreLib/Simulation.h"

class SphereMixingSimulation : public Simulation
{
public:
	void stop();
	void changeGravityStateAndResetSpheresVelocities();
	bool performStep() override;
	int getProgress() override;
	bool isMixing();
	void setMixing(bool mixing);
	static SphereMixingSimulation* create(Space* space, Bin* bin);

protected:
	Bin* bin;
	Gravity* gravity;
	SphereCollision* collision;
	double currentSphereXPos;
	double currentSphereYPos;
	double currentSphereZPos;
	bool mixing;

	SphereMixingSimulation(Space* space, Bin* bin);
	virtual void initializeGravitySequence() = 0;
	virtual void updateSpherePosition(Sphere* sphere) = 0;
	void updateSphereXPosition(Sphere* sphere);
	void updateSphereYPosition(Sphere* sphere);
	void updateSphereZPosition(Sphere* sphere);
	virtual void resolveCollisionsWithBoundaryPlanes(Sphere* sphere) = 0;
	void resolveCollisionWithYZPlane(Sphere* sphere);
	void resolveCollisionWithXZPlane(Sphere* sphere);
	void resolveCollisionWithXYPlane(Sphere* sphere);

private:
	void backupSpherePosition(Sphere* sphere);
	void resolveCollisionsWithOtherSpheres(Sphere* sphere);
	void resolveSpheresCollision(Sphere* sphere, Sphere* otherSphere);
	void revertSpherePositionIfItIsOverlappingOtherSpheres(Sphere* sphere);
};

