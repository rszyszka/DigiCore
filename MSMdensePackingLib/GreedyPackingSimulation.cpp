#include "GreedyPackingSimulation.h"
#include "SpaceFiller.h"

GreedyPackingSimulation::GreedyPackingSimulation(Space* space, GreedyPacker* packer) : Simulation(space)
{
	bin = packer->getBin();
	this->packer = packer;
	this->packer->createInitialConfiguration();
}

bool GreedyPackingSimulation::performStep()
{
	return packer->tryToPackNextCircle();
}

int GreedyPackingSimulation::getProgress()
{
	return 0; //TODO
}

double GreedyPackingSimulation::computeMathDensityLevel()
{
	return bin->getZSize() == 1 ? computeMathCircleDensityLevel() : computeMathSpheresDensityLevel();
}

double GreedyPackingSimulation::computeMathSpheresDensityLevel()
{
	double sum = 0.0;
	for (Sphere* sphere : bin->getSpheres()) {
		double v = 1.3333333333333333333 * PI * pow(sphere->getR(), 3);
		sum += v;
	}
	return sum / (double)(space->getXsize() * space->getYsize() * space->getZsize());
}

double GreedyPackingSimulation::computeMathCircleDensityLevel()
{
	double sum = 0.0;
	for (Sphere* circle : bin->getSpheres()) {
		double v = PI * circle->getR() * circle->getR();
		sum += v;
	}
	return sum / (double)(space->getXsize() * space->getYsize() * space->getZsize());
}
