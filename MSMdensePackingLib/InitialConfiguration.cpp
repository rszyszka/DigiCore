#include "InitialConfiguration.h"

void InitialConfiguration::addNewCircleInUpperLeftCorner()
{
    Sphere* sphere = sphereGenerator->generateNewSphere();
    Coords* coords = bin->getZSize() == 1 ? Coords::coords(sphere->getR(), sphere->getR()) : Coords::coords(sphere->getR(), sphere->getR(), sphere->getR());
    sphere->setCoords(*coords);
    bin->addSphere(sphere);
    delete coords;
}

InitialConfiguration::InitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator)
{
    this->bin = bin;
    this->sphereGenerator = sphereGenerator;
}

Bin* InitialConfiguration::getBin()
{
    return bin;
}

SphereGenerator* InitialConfiguration::getSphereGenerator()
{
    return sphereGenerator;
}
