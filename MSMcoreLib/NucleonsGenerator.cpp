#include "NucleonsGenerator.h"

void NucleonsGenerator::putNucleonsRandomly(Space* space, int nucleonsToInput)
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
			id_grain = c->getId();
			phase = c->getPhase();
		} while (id_grain != 0);

		c->setId(id++);
		c->setPhase(None);
		c->setIsBorder(false);
		c->setCanGrowth(true);
		space->setNoOfNucleons(space->getNoOfNucleons() + 1);
	}
	delete p;
}