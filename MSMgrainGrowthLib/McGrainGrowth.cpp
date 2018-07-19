#include "McGrainGrowth.h"
#include <tuple>

void McGrainGrowth::putStates()
{
	auto startId = space->getMaxId();
	auto start = startId > 0 ? startId : 1;
	auto end = startId + noOfQ;
	uniform_int_distribution<int> dist(start, end);


	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			for (unsigned int k = 0; k < zSize; k++)
			{
				auto c = space->getCell(new Point(i, j, k));
				if (!c->getCanGrowth()) continue;

				auto id = dist(rd);
				c->setId(id);
				c->setPhase(None);
				c->setIsBorder(false);
				c->setCanGrowth(true);
				c->setBorderNeighboursIds(std::make_tuple(0, 0));
				space->setNoOfNucleons(space->getNoOfNucleons() + 1);
			}
		}
	}
}

int McGrainGrowth::getProgress()
{
	return  progress;
}

McGrainGrowth::McGrainGrowth(Space *space, int noOfMCS, double kT) : Simulation(space), progress(0)
{
	mcsCounter = 0;

	this->xSize = space->getXsize();
	this->ySize = space->getYsize();
	this->zSize = space->getZsize();

	this->noOfCells = xSize * ySize * zSize;
	this->noOfMCS = noOfMCS;
	this->kT = kT;

	pointGen = new UniquePointGenerator(0, this->xSize - 1, 0, this->ySize - 1, 0, this->zSize - 1);
}

McGrainGrowth::McGrainGrowth(Space *space, int noOfQ, int noOfMCS, double kT) : McGrainGrowth(space, noOfMCS, kT)
{
	this->noOfQ = noOfQ;
	putStates();
}

bool McGrainGrowth::performStep()
{
	progress = 100 * mcsCounter / noOfMCS;
	uniform_int_distribution<int> dist(0, space->getNeighborhood()->getNeighboursSize() - 1);
	uniform_real_distribution<double> dist2(0, 1);

	for (int i = 0; i < noOfCells; i++)
	{
		Point *p = pointGen->nextPoint();
		Cell* analyzedCell = space->getCell(p);

		if (!analyzedCell->getCanGrowth()) continue;

		int orientation = analyzedCell->getId();
		Cell** neighbours = space->getNeighbours(p);

		int diffOrientationCounter = 0; //before reorientation
		for (int i = 0; i < space->getNeighborhood()->getNeighboursSize(); ++i)
		{
			Cell* c = neighbours[i];
			if (orientation != c->getId())
				diffOrientationCounter++;
		}

		Cell* newCell = neighbours[dist(rd)];
		if(!newCell->getCanGrowth()) continue;
		int newOrientation = newCell->getId();
		int newDiffOrientationCounter = 0; //after reoriantation
		for (int i = 0; i < space->getNeighborhood()->getNeighboursSize(); ++i)
		{
			Cell* c = neighbours[i];
			if (newOrientation != c->getId())
				newDiffOrientationCounter++;
		}

		double delta = newDiffOrientationCounter - diffOrientationCounter;
		
		if (delta <= 0 || kT > 0 && exp(-delta / kT) >= dist2(rd))
			analyzedCell->setPropertiesFromOtherCell(newCell);
	}

	pointGen->reset();
	++mcsCounter;

	return mcsCounter != noOfMCS;
}
