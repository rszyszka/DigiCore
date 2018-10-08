#include "Titanium.h"
#include <iostream>
#include <ctime>
#include <map>

void Titanium::defineGrains()
{
	int maxId = space->getMaxId();
	vector<Point*>* pointsVector = new vector<Point*>[maxId];
	int index = 0;

	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			for (unsigned int k = 0; k < zSize; k++)
			{
				Point* p = new Point(i, j, k);
				auto cell = space->getCell(p);
				index = cell->getId() - 1;
				pointsVector[index].push_back(p);
			}
		}
	}
	
	for (int i = 0; i < maxId; i++)
	{
		Grain grain(pointsVector[i], i + 1);
		grains.push_back(grain);
	}
}

void Titanium::growBetaPhaseGrains()
{
	bool changed = false;
	do {
		changed = false;
		for (Grain &grain : grains) {
			for (Point* p : grain.getPoints()) {

				Cell* cell_h = space->getCell(p);
				int oldId = cell_h->getId();
				Phase phase = cell_h->getPhase();

				if (phase == None)
				{
					Cell** neighbours = space->getNeighbours(p);
					Cell** oldNeighbours = spaceToRecover->getNeighbours(p);
					
					auto newCell = getMostFrequentValue(neighbours, oldNeighbours, grain.getId());

					if (newCell == nullptr)
						continue;

					nextStepSpace->getCell(p)->setId(newCell->getId());
					nextStepSpace->getCell(p)->setPhase(newCell->getPhase());
					nextStepSpace->getCell(p)->setIsBorder(newCell->getIsBorder());
					nextStepSpace->getCell(p)->setCanGrowth(newCell->getCanGrowth());
					nextStepSpace->getCell(p)->setBorderNeighboursIds(newCell->getBorderNeighboursIds());
					
					changed = true;
				}
			}
		}
		updateSpace();
	} while (changed);
}

void Titanium::setSpaceToRecover(Space * spaceToRecover)
{
	this->spaceToRecover = new Space(spaceToRecover);
	this->nextStepSpace = new Space(spaceToRecover);
}

void Titanium::setNextStepSpace(Space * space)
{
	this->nextStepSpace = new Space(space);
}

void Titanium::updateSpace() const
{
	for (unsigned int i = 0; i<xSize; i++)
	{
		for (unsigned int j = 0; j<ySize; j++)
		{
			for (unsigned int k = 0; k<zSize; k++)
			{
				auto cell = space->getCells()[i][j][k];
				auto nextStepCell = nextStepSpace->getCells()[i][j][k];

				cell->setPropertiesFromOtherCell(nextStepCell);
			}
		}
	}
}

Cell * Titanium::getMostFrequentValue(Cell ** cells, Cell ** oldCells, int grainCellsId) const
{
	map<int, int> cellsOfGrainNr;

	for (int i = 0; i < space->getNeighborhood()->getNeighboursSize(); i++)
	{
		if (oldCells[i]->getId() != grainCellsId)
			continue;

		auto id = cells[i]->getId();
		auto phase = cells[i]->getPhase();
		auto canGrowth = cells[i]->getCanGrowth();
		if (phase == None || !canGrowth)
			continue;

		if (cellsOfGrainNr.find(id) != cellsOfGrainNr.end()) //already exists.. increment then
			cellsOfGrainNr[id]++;
		else
			cellsOfGrainNr.emplace(id, 1);
	}

	int mostCommonNeighCounter = 0;
	int IdOfMostCommonCounter = 0;

	for (auto& x : cellsOfGrainNr) //wyznaczamy maxa
	{
		if (x.second > mostCommonNeighCounter)
		{
			IdOfMostCommonCounter = x.first;
			mostCommonNeighCounter = x.second;
		}
	}

	for (int i = 0; i < space->getNeighborhood()->getNeighboursSize(); i++)
	{
		if (cells[i]->getId() == IdOfMostCommonCounter)
			return cells[i];
	}
	
	return nullptr;
}

Titanium::Titanium(Space * space) : Simulation(space)
{
	grainGrowth = new GrainGrowth(space);
	//lamellarPhaseAddition = new LamellarPhaseGenerator(space, 3);
	//circullarInclusionsAddition = new CircullarInclusionsAddition(space, 4, 4);
}

bool Titanium::performStep()
{
	NucleonsGenerator* nucleonsGenerator = new NucleonsGenerator();
	nucleonsGenerator->putNucleonsRandomly(space, 5);
	grainGrowth->simulateContinuously();
	setSpaceToRecover(space);
	defineGrains();
	nucleonsGenerator->putNucleonsOfBetaPhaseRandomly(space, 10);
	setNextStepSpace(space);
	growBetaPhaseGrains();

	//TEST
	for (int k = 0; k < space->getZsize(); k++)
	{
		for (int i = 0; i < space->getYsize(); i++)
		{
			for (int j = 0; j < space->getXsize(); j++)
			{
				cout << spaceToRecover->getCells()[j][i][k]->getId() << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	//END TEST


	//TODO: 
	//1. Add lamellar phase 
	//2. Recover space info
	//3. Add circullar inclusions if needed

	return false;
}

int Titanium::getProgress()
{
	return progress;
}
