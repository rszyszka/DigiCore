#include "Titanium.h"

Titanium::Titanium(Space * space) : GrainGrowth(space)
{
	spaceToRecover = new Space(this->space);
}

bool Titanium::performStep()
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

				if (phase == None)
				{
					Cell** neighbours = space->getNeighbours(p);

					auto newCell = getMostFrequentValue(neighbours);

					if (newCell->getPhase() == None)
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

	return changed;
}
