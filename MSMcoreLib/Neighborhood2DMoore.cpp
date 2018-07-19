#include "Neighborhood2DMoore.h"

Neighborhood2DMoore::Neighborhood2DMoore(int xSize, int ySize, BoundaryConditions boundaryConditions) : Neighborhood2D(xSize, ySize, boundaryConditions)
{
	neighboursSize = 8;
	neighboursCoords_val = new Point*[neighboursSize];
	for (int i = 0; i < neighboursSize; i++)
		neighboursCoords_val[i] = new Point(0, 0);
}

Point** Neighborhood2DMoore::neighboursCoords(Point* p)
{
	int x = p->getX();
	int y = p->getY();

	(*neighboursCoords_val)->setXY(x - 1, y + 1);
	(*(neighboursCoords_val + 1))->setXY(x - 1, y);
	(*(neighboursCoords_val + 2))->setXY(x - 1, y - 1);
	(*(neighboursCoords_val + 3))->setXY(x, y + 1);
	(*(neighboursCoords_val + 4))->setXY(x, y - 1);
	(*(neighboursCoords_val + 5))->setXY(x + 1, y + 1);
	(*(neighboursCoords_val + 6))->setXY(x + 1, y);
	(*(neighboursCoords_val + 7))->setXY(x + 1, y - 1);

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood2DMoore::getNeighborhoodType()
{
	return NeighborhoodType::Moore;
}