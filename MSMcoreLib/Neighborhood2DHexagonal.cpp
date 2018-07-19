#include "Neighborhood2DHexagonal.h"

Neighborhood2DHexagonal::Neighborhood2DHexagonal(int xSize, int ySize, BoundaryConditions boundaryConditions) : Neighborhood2D(xSize, ySize, boundaryConditions)
{
	neighboursSize = 6;
	neighboursCoords_val = new Point*[neighboursSize];
	for (int i = 0; i < neighboursSize; i++)
		neighboursCoords_val[i] = new Point(0, 0);
}

Point** Neighborhood2DHexagonal::neighboursCoords(Point* p)
{
	int x = p->getX();
	int y = p->getY();

	(*neighboursCoords_val)->setXY(x + 1, y);
	(*(neighboursCoords_val + 1))->setXY(x - 1, y);
	(*(neighboursCoords_val + 2))->setXY(x, y + 1);
	(*(neighboursCoords_val + 3))->setXY(x, y - 1);

	std::uniform_int_distribution<int> dist(0, 1);
	int randValue = dist(rd);

	if (randValue == 0)
	{
		(*(neighboursCoords_val + 4))->setXY(x - 1, y + 1);
		(*(neighboursCoords_val + 5))->setXY(x + 1, y - 1);
	}
	else
	{
		(*(neighboursCoords_val + 4))->setXY(x + 1, y + 1);
		(*(neighboursCoords_val + 5))->setXY(x - 1, y - 1);
	}

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood2DHexagonal::getNeighborhoodType()
{
	return NeighborhoodType::Hexagonal;
}