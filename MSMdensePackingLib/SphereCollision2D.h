#pragma once
#include "SphereCollision.h"

class SphereCollision2D : public SphereCollision
{
public:
	void determineAuxiliaryVelocitiesByRotatingForward(Sphere* sphere, Sphere* otherSphere) override;
	Velocity determineFinalVelocityByRotatingBackward(Velocity* v) override;
	double computeMass(Sphere* sphere) override;

private:
	double angle;
};

