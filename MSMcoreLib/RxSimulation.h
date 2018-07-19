#pragma once
#include "Space.h"
#include "Simulation.h"

class RxSimulation abstract : public Simulation 
{
protected:
	//Nucleation *nucleonGenerator; //final
	Space *nextStepSpace;
	int DifferentNucleonSize;

public:
	__declspec(dllexport) RxSimulation(Space *space);//, Nucleation *nucleonGenerator);
	__declspec(dllexport) ~RxSimulation();
};