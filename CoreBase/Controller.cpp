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
#include "IOStreamer.h"
#include <fstream>


#include <map>

using namespace std;

Controller::~Controller()
{
	delete space;
	delete grainGrowth;
	delete titaniumGeneration;
}

Controller::Controller()
{

}

void Controller::StartProcess()
{
	cout << "\ngrowing grains..." << endl;
	grainGrowth->simulateContinuously();
	cout << "\ngenerating titanium..." << endl;
	titaniumGeneration->simulateContinuously();
}

void Controller::PrepareProcess(int* argc, char** argv[])
{
	int sizeX = 500;
	int sizeY = 500;
	int sizeZ = 1;
	space = new Space(sizeX, sizeY, sizeZ, new Neighborhood3DMoore(sizeX, sizeY,sizeZ, Periodic));

	NucleonsGenerator* nucleonsGenerator = new NucleonsGenerator();
	nucleonsGenerator->putNucleonsRandomly(space, 10);
	
	grainGrowth = new GrainGrowth(space);

	int twinWidth = 5;
	int inclusionMaxRadius = 15;
	int inclusionsCoverage = 0;
	int betaPhaseNucleonsToPut = 1500;
	titaniumGeneration = new Titanium(space, twinWidth, inclusionMaxRadius, inclusionsCoverage, betaPhaseNucleonsToPut);
}


void Controller::CloseProcess()
{
	cout << "Finalize" << endl;
	
	ofstream out_visio("result_v15.txt");
	out_visio << space->getXsize() << " " << space->getYsize() << " " << space->getZsize() << endl;
	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				out_visio << j << " " << i << " " << k << " " << space->getCells()[j][i][k]->getId()<<endl;
			}
		}
	}


	//Just for test
	//ofstream out0("result.txt");
	//for (int k = 0; k < space->getZsize(); k++)
	//{
	//	for (int i = 0; i < space->getYsize(); i++)
	//	{
	//		for (int j = 0; j < space->getXsize(); j++)
	//		{
	//			out0 << space->getCells()[j][i][k]->getId() << " ";
	//		}
	//		out0 << endl;
	//	}
	//	out0 << endl;
	//}
	//out0.close();


	//ofstream out1("twins.txt");
	//for (int k = 0; k < space->getZsize(); k++)
	//{
	//	for (int i = 0; i < space->getYsize(); i++)
	//	{
	//		for (int j = 0; j < space->getXsize(); j++)
	//		{
	//			if (space->getCells()[j][i][k]->getPhase() == Twin)
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
}