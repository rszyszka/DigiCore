#pragma once
#include "LargestSphereGenerator.h"
class OscillatingSphereGenerator :
    public LargestSphereGenerator
{
public:
    OscillatingSphereGenerator(int minRadius, int maxRadius, int counter);
    void resetMaxRadius() override;

private:
     const int originCounter;
     const int realOriginMaxRadius;
     int counter;
     int modifier;

     void changeDirectionIfNecessary();
};

