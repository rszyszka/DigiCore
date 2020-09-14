#pragma once
#include "SphereMixingSimulation.h"

class SphereMixingSimulation2D : public SphereMixingSimulation
{
public:
	SphereMixingSimulation2D(Space* space, Bin* bin);

protected:
	void initializeGravitySequence() override;
	void updateSpherePosition(Sphere* sphere) override;
	void resolveCollisionsWithBoundaryPlanes(Sphere* sphere) override;
};

