#include "TangentialCirclesInitialConfiguration.h"

TangentialCirclesInitialConfiguration::TangentialCirclesInitialConfiguration(Bin* bin, SphereGenerator* sphereGenerator) : InitialConfiguration(bin, sphereGenerator)
{
}

void TangentialCirclesInitialConfiguration::init()
{
	addNewCircleInUpperLeftCorner();
	addNewCircleNextToFirstOne();
}

void TangentialCirclesInitialConfiguration::addNewCircleNextToFirstOne()
{
    Sphere* sphere = sphereGenerator->generateNewSphere();
    Sphere* sphereInBin = bin->getSpheres().at(0);

    int rC = sphere->getR();
    int rA = sphereInBin->getR();

    Coords* coordsA = sphereInBin->getCoords();
    double y = sqrt(pow(rC + rA, 2) - pow(rC - coordsA->getX(), 2)) + coordsA->getY();

    sphere->setCoords(Coords(rC, y, sphereInBin->getCoords()->getZ()));
    bin->addSphere(sphere);
}
