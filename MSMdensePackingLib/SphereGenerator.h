#pragma once
#include "Sphere.h"

class SphereGenerator
{
public:
    virtual Sphere* generateNewSphere() = 0;
    virtual bool setLowerRadiusIfPossible(int currentRadiusOfFailedCirclePackingAttempt) = 0;
    virtual void resetMaxRadius() = 0;
};
