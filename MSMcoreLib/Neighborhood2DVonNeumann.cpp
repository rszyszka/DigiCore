#include "Neighborhood2DVonNeumann.h"

Neighborhood2DVonNeumann::Neighborhood2DVonNeumann(int xSize, int ySize, BoundaryConditions boundaryConditions) : Neighborhood2D(xSize, ySize, boundaryConditions)
{
	neighboursSize = 4;
	neighboursCoords_val = new Point*[neighboursSize];
	for (int i = 0; i < neighboursSize; i++)
		neighboursCoords_val[i] = new Point(0, 0);
}

Point** Neighborhood2DVonNeumann::neighboursCoords(Point* p)
{
	int x = p->getX();
	int y = p->getY();

	(*neighboursCoords_val)->setXY(x + 1, y);
	(*(neighboursCoords_val + 1))->setXY(x - 1, y);
	(*(neighboursCoords_val + 2))->setXY(x, y + 1);
	(*(neighboursCoords_val + 3))->setXY(x, y - 1);

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood2DVonNeumann::getNeighborhoodType()
{
	return NeighborhoodType::VonNeumann;
}