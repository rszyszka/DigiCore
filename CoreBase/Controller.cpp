#pragma once
#include "stdafx.h"
#include "Controller.h"
#include <iostream>
#include "McGrainGrowth.h"
#include "GrainGrowth.h"
#include "NucleonsGenerator.h"
#include "Neighborhood2DVonNeumann.h"
#include "Neighborhood3DVonNeumann.h"
#include "Neighborhood2DMoore.h"
#include "Neighborhood3DMoore.h"
#include "Neighborhood2DCircular.h"
#include "Neighborhood3DCircular.h"
#include "Neighborhood2DPentagonal.h"
#include "Neighborhood3DPentagonal.h"
#include "Neighborhood2DHexagonal.h"
#include "Neighborhood3DHexagonal.h"
#include <fstream>


#include <map>

using namespace std;

Controller::~Controller()
{
	delete space;
	delete grainGrowth;
	delete lamellarPhaseAddition;
	delete circullarInclusionsAddition;

}

Controller::Controller()
{

}

void Controller::StartProcess()
{
	cout << "growing the grains..." << endl;
	grainGrowth->simulateContinuously();
	cout << "adding lammelar phase..." << endl;
	lamellarPhaseAddition->simulateContinuously();
	circullarInclusionsAddition->simulateContinuously();
}

void Controller::PrepareProcess(int* argc, char** argv[])
{
	int sizeX = 100;
	int sizeY = 100;
	int sizeZ = 10;
	space = new Space(sizeX, sizeY, sizeZ, new Neighborhood3DPentagonal(sizeX, sizeY,sizeZ, Absorbent));
	
	//simulation = new McGrainGrowth(space, 10, 2, 0.3);
	
	grainGrowth = new GrainGrowth(space);
	NucleonsGenerator* nucleonsGenerator = new NucleonsGenerator();
	nucleonsGenerator->putNucleonsRandomly(space, 9);

	lamellarPhaseAddition = new LamellarPhaseGenerator(space, 3);
	circullarInclusionsAddition = new CircullarInclusionsAddition(space,4,4);

}


void Controller::CloseProcess()
{
	cout << "Finalize" << endl;
	
	//Just for test
	ofstream out1("twins.txt");
	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				if (space->getCells()[j][i][k]->getPhase() != Twin)
					out1 << space->getCells()[j][i][k]->getId() << " ";
				else
					out1 << " " << " ";
			}
			out1 << endl;
		}
		out1 << endl;
	}
	out1.close();

	ofstream out("inclusions.txt");
	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				if (space->getCells()[j][i][k]->getPhase() == Inclusion)
					out << 1 << " ";
				else
					out << 0 << " ";
			}
			out << endl;
		}
		out << endl;
	}
	out.close();
	getchar();
}