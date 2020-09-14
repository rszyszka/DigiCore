#include "DensePackingSimulation.h"
#include "RandomSphereGenerator.h"
#include "TangentialCirclesInitialConfiguration.h"
#include "SpaceFiller.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;

DensePackingSimulation::DensePackingSimulation(Space* space, int minR, int maxR) : Simulation(space)
{
    srand(time(nullptr));

    this->minR = minR;
    this->maxR = maxR;
    numberOfFilledCells = 0;
    bin = new Bin(space->getXsize(), space->getYsize(), space->getZsize());
    mixingSpheresSimulation = SphereMixingSimulation::create(space, bin);

    HolesFinder* holesFinder = HolesFinder::create(bin);
    HolesFinder::penaltyType = PenaltyType::GLOBAL;
    HolesFinder::PENALTY_VALUE = 0.02;
    SphereGenerator* sphereGenerator = new RandomSphereGenerator(minR, maxR);
    InitialConfiguration* initialConfiguration = new TangentialCirclesInitialConfiguration(bin, sphereGenerator);
    GreedyPacker* packer = new GreedyPacker(initialConfiguration, holesFinder);
    greedyPackingSimulation = new GreedyPackingSimulation(space, packer);
}

bool DensePackingSimulation::performStep()
{
    cout << "STEP 1: Greedy packing algorithm" << endl;
    cout.precision(17);
    performGreedyPacking();
    cout << "Math density: " << fixed << greedyPackingSimulation->computeMathDensityLevel() << endl;
    cout<< "STEP 1 finished."<<endl;
    cout<<"STEP 2: Mixing balls and trying to pack additional spheres"<<endl;
    int squaredDimension = bin->getZSize() == 1 ? 4 : 6;
    for (int i = 0; i < squaredDimension; i++) {
        milliseconds mixingPeriod = milliseconds(8500);
        auto startTime = high_resolution_clock::now();
        while (duration_cast<milliseconds>(high_resolution_clock::now() - startTime) <= milliseconds(30000)) {
            auto periodStartTime = high_resolution_clock::now();
            while (duration_cast<microseconds>(high_resolution_clock::now() - periodStartTime) <= mixingPeriod) {
                mixingSpheresSimulation->performStep();
            }
            performGreedyPacking();
            greedyPackingSimulation->computeMathDensityLevel();
            mixingPeriod = mixingPeriod <= milliseconds(1000) ? milliseconds(1000) : milliseconds(mixingPeriod - milliseconds(2500));
        }
        cout << "Math density: " << fixed << greedyPackingSimulation->computeMathDensityLevel() << endl;
        cout<<"Changing gravity state"<<endl;
        mixingSpheresSimulation->changeGravityStateAndResetSpheresVelocities();
    }
    cout<<"STEP 2 finished."<<endl;
    cout<<"STEP 3: Filling CA space"<<endl;
    SpaceFiller* filler = new SpaceFiller(space);
    filler->fillWithAllSpheres(bin);
    numberOfFilledCells = filler->getNumberOfFilledCells();
    cout<<"Simulation completed"<<endl;
    cout<<"Math density: " <<fixed<< greedyPackingSimulation->computeMathDensityLevel() <<endl;
    return false;
}

int DensePackingSimulation::getProgress()
{
    return 0; //TODO
}

Bin* DensePackingSimulation::getBin()
{
    return bin;
}

void DensePackingSimulation::performGreedyPacking()
{
    greedyPackingSimulation->simulateContinuously();
}

double DensePackingSimulation::computeVoxelDensityLevel()
{
    return numberOfFilledCells / (double)(space->getXsize() * space->getYsize() * space->getZsize());
}
