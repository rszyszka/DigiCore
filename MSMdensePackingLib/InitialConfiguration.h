#pragma once
#include "Bin.h"
#include "SphereGenerator.h"

class InitialConfiguration
{
public:
    InitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator);
    virtual void init() = 0;
    Bin* getBin();
    SphereGenerator* getSphereGenerator();

protected:
    Bin* bin;
    SphereGenerator* sphereGenerator;
    void addNewCircleInUpperLeftCorner();
};
