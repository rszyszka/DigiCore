#include "GreedyPacker.h"

GreedyPacker::GreedyPacker(InitialConfiguration* initialConfiguration, HolesFinder* holesFinder)
{
    this->initialConfiguration = initialConfiguration;
    this->bin = initialConfiguration->getBin();
    this->sphereGenerator = initialConfiguration->getSphereGenerator();
    this->holesFinder = holesFinder;
}

void GreedyPacker::createInitialConfiguration()
{
    initialConfiguration->init();
}

Bin* GreedyPacker::getBin()
{
    return bin;
}

bool GreedyPacker::tryToPackNextCircle()
{
    Sphere* sphere = sphereGenerator->generateNewSphere();
    vector<Hole*> holes = holesFinder->findForSphere(sphere);

    if (holes.empty()) {
        return tryToGenerateAndPackNewSphereWithDiminishedRadius(sphere);
    }

    Hole* bestHole = holesFinder->findHoleWithMaximumDegree();
    sphere->setCoords(*bestHole->getCoords());
    sphereGenerator->resetMaxRadius();
    return bin->addSphere(sphere);
}

bool GreedyPacker::tryToGenerateAndPackNewSphereWithDiminishedRadius(Sphere* sphere)
{
    bool diminished = sphereGenerator->setLowerRadiusIfPossible(sphere->getR());
    if (diminished) {
        return tryToPackNextCircle();
    }
    return false;
}
