#include "Neighborhood2D.h"

Neighborhood2D::Neighborhood2D(int xSize, int ySize, BoundaryConditions boundaryConditions) : Neighborhood(boundaryConditions)
{
	this->boundaryConditions = boundaryConditions;
	this->xSize = xSize;
	this->ySize = ySize;
}

Point** Neighborhood2D::getNeighboursCoords(Point* p)
{
	Point** neighbours = neighboursCoords(p);

	if (boundaryConditions == BoundaryConditions(Periodic))
	{
		for (int i = 0; i < neighboursSize; i++)
		{
			Point* pp = neighbours[i];

			int x = pp->getX();
			int y = pp->getY();

			if (x < 0)
				pp->setX(xSize + x);
			else if (x >= xSize)
				pp->setX(x - xSize);

			if (y < 0)
				pp->setY(ySize + y);
			else if (y >= ySize)
				pp->setY(y - ySize);
		}
	}
	else if (boundaryConditions == BoundaryConditions(Absorbent))
	{
		for (int i = 0; i < neighboursSize; i++)
		{
			Point *pp = neighbours[i];

			int x = pp->getX();
			int y = pp->getY();

			if (x < 0)
				pp->setX(0);
			else if (x >= xSize)
				pp->setX(xSize - 1);

			if (y < 0)
				pp->setY(0);
			else if (y >= ySize)
				pp->setY(ySize - 1);
		}
	}
	else if (boundaryConditions == BoundaryConditions(Reflecting))
	{
		for (int i = 0; i < neighboursSize; i++)
		{
			Point *pp = neighbours[i];

			int x = pp->getX();
			int y = pp->getY();

			if (x < 0)
				pp->setX(-x - 1);
			else if (x >= xSize)
				pp->setX(xSize - (x - xSize + 1));

			if (y < 0)
				pp->setY(-y - 1);
			else if (y >= ySize)
				pp->setY(ySize - (y - ySize + 1));
		}
	}

	return neighbours;
}