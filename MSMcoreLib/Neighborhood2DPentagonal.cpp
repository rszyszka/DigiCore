#include "Neighborhood2DPentagonal.h"

Neighborhood2DPentagonal::Neighborhood2DPentagonal(int xSize, int ySize, BoundaryConditions boundaryConditions) : Neighborhood2D(xSize, ySize, boundaryConditions)
{
	neighboursSize = 5;
	neighboursCoords_val = new Point*[neighboursSize];
	for (int i = 0; i < neighboursSize; i++)
		neighboursCoords_val[i] = new Point(0, 0);
}

Point** Neighborhood2DPentagonal::neighboursCoords(Point* p)
{
	int x = p->getX();
	int y = p->getY();

	std::uniform_int_distribution<int> dist(0, 3);
	int randValue = dist(rd);

	if (randValue == 0)
	{
		(*neighboursCoords_val)->setXY(x, y + 1);
		(*(neighboursCoords_val + 1))->setXY(x - 1, y + 1);
		(*(neighboursCoords_val + 2))->setXY(x - 1, y);
		(*(neighboursCoords_val + 3))->setXY(x - 1, y - 1);
		(*(neighboursCoords_val + 4))->setXY(x, y - 1);
	}
	else if (randValue == 1)
	{
		(*neighboursCoords_val)->setXY(x, y + 1);
		(*(neighboursCoords_val + 1))->setXY(x + 1, y + 1);
		(*(neighboursCoords_val + 2))->setXY(x + 1, y);
		(*(neighboursCoords_val + 3))->setXY(x + 1, y - 1);
		(*(neighboursCoords_val + 4))->setXY(x, y - 1);
	}
	else if (randValue == 2)
	{
		(*neighboursCoords_val)->setXY(x - 1, y);
		(*(neighboursCoords_val + 1))->setXY(x - 1, y - 1);
		(*(neighboursCoords_val + 2))->setXY(x, y - 1);
		(*(neighboursCoords_val + 3))->setXY(x + 1, y - 1);
		(*(neighboursCoords_val + 4))->setXY(x + 1, y);
	}
	else
	{
		(*neighboursCoords_val)->setXY(x - 1, y);
		(*(neighboursCoords_val + 1))->setXY(x - 1, y + 1);
		(*(neighboursCoords_val + 2))->setXY(x, y + 1);
		(*(neighboursCoords_val + 3))->setXY(x + 1, y + 1);
		(*(neighboursCoords_val + 4))->setXY(x + 1, y);
	}

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood2DPentagonal::getNeighborhoodType()
{
	return NeighborhoodType::Pentagonal;
}