#include "Neighborhood3D.h"

Neighborhood3D::Neighborhood3D(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions) : Neighborhood(boundaryConditions)
{
	this->boundaryConditions = boundaryConditions;
	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;
}

Point** Neighborhood3D::getNeighboursCoords(Point* p)
{
	Point** neighbours = neighboursCoords(p);

	if (boundaryConditions == BoundaryConditions(Periodic))
	{
		for (int i = 0; i < neighboursSize; i++)
		{
			Point* pp = neighbours[i];

			int x = pp->getX();
			int y = pp->getY();
			int z = pp->getZ();

			if (x < 0)
				pp->setX(xSize + x);
			else if (x >= xSize)
				pp->setX(x - xSize);

			if (y < 0)
				pp->setY(ySize + y);
			else if (y >= ySize)
				pp->setY(y - ySize);

			if (z < 0)
				pp->setZ(zSize + z);
			else if (z >= zSize)
				pp->setZ(z - zSize);
		}
	}
	else if (boundaryConditions == BoundaryConditions(Absorbent))
	{
		for (int i = 0; i < neighboursSize; i++)
		{
			Point *pp = neighbours[i];

			int x = pp->getX();
			int y = pp->getY();
			int z = pp->getZ();

			if (x < 0)
				pp->setX(0);
			else if (x >= xSize)
				pp->setX(xSize - 1);

			if (y < 0)
				pp->setY(0);
			else if (y >= ySize)
				pp->setY(ySize - 1);

			if (z < 0)
				pp->setZ(0);
			else if (z >= zSize)
				pp->setZ(zSize - 1);
		}
	}
	else if (boundaryConditions == BoundaryConditions(Reflecting))
	{
		for (int i = 0; i < neighboursSize; i++)
		{
			Point *pp = neighbours[i];

			int x = pp->getX();
			int y = pp->getY();
			int z = pp->getZ();

			if (x < 0)
				pp->setX(-x - 1);
			else if (x >= xSize)
				pp->setX(xSize - (x - xSize + 1));

			if (y < 0)
				pp->setY(-y - 1);
			else if (y >= ySize)
				pp->setY(ySize - (y - ySize + 1));

			if (z < 0)
				pp->setZ(-z - 1);
			else if (z >= zSize)
				pp->setZ(zSize - (z - zSize + 1));
		}
	}

	return neighbours;
}