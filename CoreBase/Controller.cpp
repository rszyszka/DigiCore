#pragma once
#include "stdafx.h"
#include "Controller.h"
#include <iostream>
#include "McGrainGrowth.h"
#include "GrainGrowth.h"
#include "Titanium.h"
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
	delete titaniumGeneration;
}

Controller::Controller()
{

}

void Controller::StartProcess()
{
	cout << "\ngenerating titanium..." << endl;
	titaniumGeneration->simulateContinuously();
	//cout << "\nadding lamellar phase..." << endl;
	//lamellarPhaseAddition->simulateContinuously();
	//circullarInclusionsAddition->simulateContinuously();
}

void Controller::PrepareProcess(int* argc, char** argv[])
{
	int sizeX = 20;
	int sizeY = 20;
	int sizeZ = 1;
	space = new Space(sizeX, sizeY, sizeZ, new Neighborhood3DMoore(sizeX, sizeY,sizeZ, Absorbent));
	
	//simulation = new McGrainGrowth(space, 10, 2, 0.3);
	/*grainGrowth = new GrainGrowth(space);
	NucleonsGenerator* nucleonsGenerator = new NucleonsGenerator();
	nucleonsGenerator->putNucleonsRandomly(space, 9);
	lamellarPhaseAddition = new LamellarPhaseGenerator(space, 3);
	circullarInclusionsAddition = new CircullarInclusionsAddition(space,4,4);*/

	titaniumGeneration = new Titanium(space);
}


void Controller::CloseProcess()
{
	cout << "Finalize" << endl;

	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				cout << space->getCells()[j][i][k]->getId() << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	//Just for test
	//ofstream out1("twins.txt");
	//for (int k = 0; k < space->getZsize(); k++)
	//{
	//	for (int i = 0; i < space->getYsize(); i++)
	//	{
	//		for (int j = 0; j < space->getXsize(); j++)
	//		{
	//			if (space->getCells()[j][i][k]->getPhase() != Twin)
	//				out1 << space->getCells()[j][i][k]->getId() << " ";
	//			else
	//				out1 << " " << " ";
	//		}
	//		out1 << endl;
	//	}
	//	out1 << endl;
	//}
	//out1.close();

	//ofstream out("inclusions.txt");
	//for (int k = 0; k < space->getZsize(); k++)
	//{
	//	for (int i = 0; i < space->getYsize(); i++)
	//	{
	//		for (int j = 0; j < space->getXsize(); j++)
	//		{
	//			if (space->getCells()[j][i][k]->getPhase() == Inclusion)
	//				out << 1 << " ";
	//			else
	//				out << 0 << " ";
	//		}
	//		out << endl;
	//	}
	//	out << endl;
	//}
	//out.close();
	getchar();
}