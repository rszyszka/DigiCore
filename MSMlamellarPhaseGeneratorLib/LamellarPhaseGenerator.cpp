#include "LamellarPhaseGenerator.h"
#include <ctime>

LamellarPhaseGenerator::LamellarPhaseGenerator(Space * space) : Simulation(space)
{
	srand(time(nullptr));
	numberOfGrains = this->space->getMaxId();
	secondPhaseSpace = new Space();
	
}

bool LamellarPhaseGenerator::performStep()
{
	double alpha = (rand() % 91) * pi() / 180.0;
	



	return false;
}

vector<Grain> LamellarPhaseGenerator::getGrainsAngles() { return vector<Grain>(); }
