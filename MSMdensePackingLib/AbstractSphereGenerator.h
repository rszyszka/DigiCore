#pragma once
#include "SphereGenerator.h"
class AbstractSphereGenerator : public SphereGenerator
{
public:
    AbstractSphereGenerator(int minRadius, int maxRadius);
    bool setLowerRadiusIfPossible(int currentCircleRadius) override;
    void resetMaxRadius() override;

protected:
     const int minRadius;
     int originMaxRadius;
     int maxRadius;
};

