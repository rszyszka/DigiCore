#pragma once
#include "SphereMixingSimulation.h"

class SphereMixingSimulation3D : public SphereMixingSimulation
{
public:
	SphereMixingSimulation3D(Space* space, Bin* bin);

protected:
	void initializeGravitySequence() override;
	void updateSpherePosition(Sphere* sphere) override;
	void resolveCollisionsWithBoundaryPlanes(Sphere* sphere) override;
};

