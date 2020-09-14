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
#include <DensePackingSimulation.h>
#include <DensePackingSimulation.h>

#include <map>


using namespace std;

Controller::~Controller()
{
	delete space;
	delete simulation;
}

Controller::Controller()
{

}

void Controller::StartProcess()
{
	simulation->simulateContinuously();

	//cout << "\ngrowing grains..." << endl;
	//simulation->simulateContinuously();
}

void Controller::PrepareProcess(int* argc, char** argv[])
{
	int sizeX = 200;
	int sizeY = 200;
	int sizeZ = 200;
	space = new Space(sizeX, sizeY, sizeZ, new Neighborhood3DMoore(sizeX, sizeY, sizeZ, Absorbent));

	bin = new Bin(space->getXsize(), space->getYsize(), space->getZsize());
	simulation = new DensePackingSimulation(space, 10, 40);

	//IOStreamer::LoadSpace(space, "packingResult.txt");
	//simulation = new GrainGrowth(space);
}


void Controller::CloseProcess()
{
	//Just for tests

	//cout << "Finalize" << endl;

	////ofstream out_visio("packingResult.txt");
	//ofstream out_visio("grainGrowthResult.txt");
	//out_visio << space->getXsize() << " " << space->getYsize() << " " << space->getZsize() << endl;
	//for (int k = 0; k < space->getZsize(); k++)
	//{
	//	for (int i = 0; i < space->getYsize(); i++)
	//	{
	//		for (int j = 0; j < space->getXsize(); j++)
	//		{
	//			int id = space->getCells()[j][i][k]->getId();
	//			if (id != 0) out_visio << j << " " << i << " " << k << " " << id << endl;
	//		}
	//	}
	//}
	//out_visio.close();
}