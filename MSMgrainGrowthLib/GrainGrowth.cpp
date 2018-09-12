#include "GrainGrowth.h"
#include <iostream>
#include <ctime>
#include <map>

GrainGrowth::GrainGrowth(Space *space) : Simulation(space)
{
	srand(time(nullptr));

	nextStepSpace = new Space(this->space);

	progress = 100 / (xSize * ySize * zSize);
}

int GrainGrowth::getProgress()
{
	return progress;
}

bool GrainGrowth::performStep()
{
	bool changed = false;
	int progress_counter = 0;

	Point *p = new Point(0, 0, 0);

	for (unsigned int i = 0; i<xSize; i++)
	{
		for (unsigned int j = 0; j<ySize; j++)
		{
			for (unsigned int k = 0; k<zSize; k++)
			{
				p->setXYZ(i, j, k);

				Cell* cell_h = space->getCell(p);
				int oldId = cell_h->getId();
				Phase phase = cell_h->getPhase();

				if (oldId == 0)
				{
					Cell** neighbours = space->getNeighbours(p);

					auto newCell = getMostFrequentValue(neighbours);

					if (newCell->getId() == 0)
						continue;

					nextStepSpace->getCell(p)->setId(newCell->getId());
					nextStepSpace->getCell(p)->setPhase(newCell->getPhase());
					nextStepSpace->getCell(p)->setIsBorder(newCell->getIsBorder());
					nextStepSpace->getCell(p)->setCanGrowth(newCell->getCanGrowth());
					nextStepSpace->getCell(p)->setBorderNeighboursIds(newCell->getBorderNeighboursIds());
					
					changed = true;
				}
				else
					++progress_counter;
			}
		}
	}

	updateSpace();

	progress = 100 * progress_counter / (xSize * ySize * zSize);
	cout << progress << " ";

	return changed;
}

void GrainGrowth::updateSpace() const
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

Cell* GrainGrowth::getMostFrequentValue(Cell** cells) const
{
	map<int, int> cellsOfGrainNr;

	for (int i = 0; i < space->getNeighborhood()->getNeighboursSize(); i++)
	{
		auto id = cells[i]->getId();
		auto canGrowth = cells[i]->getCanGrowth();
		if (id == 0 || !canGrowth)
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
