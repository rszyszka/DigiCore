#include "NucleonsGenerator.h"

void NucleonsGenerator::putNucleonsRandomly(Space* space, int nucleonsToInput)
{
	int id = space->getMaxId() + 1;
	int id_grain = 0;
	Point *p = new Point();
	for (int i = 0; i < nucleonsToInput; i++)
	{
		Cell *c;
		do
		{
			p->setXYZ(rand() % space->getXsize(), rand() % space->getYsize(), rand() % space->getZsize());
			c = space->getCell(p);
			id_grain = c->getId();
		} while (id_grain != 0);

		c->setId(id++);
		c->setPhase(None);
		c->setIsBorder(false);
		c->setCanGrowth(true);
		space->setNoOfNucleons(space->getNoOfNucleons() + 1);
	}
	delete p;
}

//puts nucleons of beta phase randomly in whole space
void NucleonsGenerator::putNucleonsOfBetaPhaseRandomly(Space * space, int nucleonsToInput)
{
	int id = space->getMaxId() + 1;
	int id_grain = 0;
	Point *p = new Point();
	for (int i = 0; i < nucleonsToInput; i++)
	{
		Cell *c;
		Phase phase;
		do
		{
			p->setXYZ(rand() % space->getXsize(), rand() % space->getYsize(), rand() % space->getZsize());
			c = space->getCell(p);
			phase = c->getPhase();
		} while (phase != None);

		c->setId(id++);
		c->setPhase(Beta);
		c->setIsBorder(false);
		c->setCanGrowth(true);
		space->setNoOfNucleons(space->getNoOfNucleons() + 1);
	}
	delete p;
}

//puts nucleons of beta phase randomly in one particular grain
void NucleonsGenerator::putNucleonsOfBetaPhaseRandomly(Space * space, int nucleonsToInput, vector<Point*> grainPoints)
{
	int id = space->getMaxId() + 1;
	int id_grain = 0;
	int pointsVectorSize = grainPoints.size();
	for (int i = 0; i < nucleonsToInput; i++)
	{
		Cell *c;
		Phase phase;
		do
		{
			int randIndex = rand() % pointsVectorSize;
			c = space->getCell(grainPoints[randIndex]);
			phase = c->getPhase();
		} while (phase != None);

		c->setId(id++);
		c->setPhase(Beta);
		c->setIsBorder(false);
		c->setCanGrowth(true);
		space->setNoOfNucleons(space->getNoOfNucleons() + 1);
	}
}