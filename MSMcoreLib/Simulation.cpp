#include "Simulation.h"

Simulation::~Simulation()
{

}

void Simulation::simulateContinuously()
{
	while (notFinished == performStep())
	{
	}
}
void Simulation::nextStep()
{
	for (int i = 0; i < 10 && notFinished; i++)
		notFinished = performStep();
}

Simulation::Simulation(Space* space) : space(space)
{
	this->space = space;
	this->xSize = space->getXsize();
	this->ySize = space->getYsize();
	this->zSize = space->getZsize();

	notFinished = true;
	stepByStep = false;
}


void Simulation::simulateWithOneThread()
{
	if (stepByStep)
		nextStep();
	else
		simulateContinuously();
}

Space* Simulation::getSpace() const
{
	return space;
}

void Simulation::setSpace(Space* space)
{
	this->space = space;
}

bool Simulation::isFinished() const
{
	return !notFinished;
}