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
}

Controller::Controller()
{

}

void Controller::StartProcess()
{
	/*grainGrowth->simulateContinuously();
	lamellarPhaseAddition->simulateContinuously();*/
	circullarInclusionsAddition->simulateContinuously();
}

void Controller::PrepareProcess(int* argc, char** argv[])
{
	int sizeX = 1000;
	int sizeY = 1000;
	int sizeZ = 1;
	space = new Space(sizeX, sizeY, sizeZ, new Neighborhood3DPentagonal(sizeX, sizeY,sizeZ, Absorbent));
	
	//simulation = new McGrainGrowth(space, 10, 2, 0.3);
	
	grainGrowth = new GrainGrowth(space);
	NucleonsGenerator* nucleonsGenerator = new NucleonsGenerator();
	nucleonsGenerator->putNucleonsRandomly(space, 3);

	lamellarPhaseAddition = new LamellarPhaseGenerator(space);
	circullarInclusionsAddition = new CircullarInclusionsAddition(space);

}


void Controller::CloseProcess()
{
	cout << "Finalize" << endl;
	/*
	//Just for test
	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				cout << space->getCells()[i][j][k]->getId() << " ";
			}
			cout << endl;
		}
		cout << endl;
	}


	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				cout << lamellarPhaseAddition->getSecondPhaseSpace()->getCells()[i][j][k]->getId() << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	*/

	ofstream out("result.txt");
	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				if (circullarInclusionsAddition->getSpace()->getCells()[j][i][k]->getPhase() == Inclusion)
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