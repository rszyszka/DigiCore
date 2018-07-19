#include "Neighborhood3DPentagonal.h"

Neighborhood3DPentagonal::Neighborhood3DPentagonal(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions) : Neighborhood3D(xSize, ySize, zSize, boundaryConditions)
{
	neighboursSize = 17;
	neighboursCoords_val = new Point*[neighboursSize];
	for (int i = 0; i < neighboursSize; i++)
		neighboursCoords_val[i] = new Point(0, 0, 0);
}


Point** Neighborhood3DPentagonal::neighboursCoords(Point* p)
{
	int x = p->getX();
	int y = p->getY();
	int z = p->getZ();

	std::uniform_int_distribution<int> dist(0, 3);
	int randValue = dist(rd);

	(*neighboursCoords_val)->setXYZ(x, y, z - 1);
	(*(neighboursCoords_val + 1))->setXYZ(x, y, z + 1);

	if (randValue == 0)
	{
		(*(neighboursCoords_val + 2))->setXYZ(x, y + 1, z);
		(*(neighboursCoords_val + 3))->setXYZ(x, y + 1, z - 1);
		(*(neighboursCoords_val + 4))->setXYZ(x, y + 1, z + 1);

		(*(neighboursCoords_val + 5))->setXYZ(x - 1, y + 1, z);
		(*(neighboursCoords_val + 6))->setXYZ(x - 1, y + 1, z - 1);
		(*(neighboursCoords_val + 7))->setXYZ(x - 1, y + 1, z + 1);

		(*(neighboursCoords_val + 8))->setXYZ(x - 1, y, z);
		(*(neighboursCoords_val + 9))->setXYZ(x - 1, y, z - 1);
		(*(neighboursCoords_val + 10))->setXYZ(x - 1, y, z + 1);

		(*(neighboursCoords_val + 11))->setXYZ(x - 1, y - 1, z);
		(*(neighboursCoords_val + 12))->setXYZ(x - 1, y - 1, z - 1);
		(*(neighboursCoords_val + 13))->setXYZ(x - 1, y - 1, z + 1);

		(*(neighboursCoords_val + 14))->setXYZ(x, y - 1, z);
		(*(neighboursCoords_val + 15))->setXYZ(x, y - 1, z - 1);
		(*(neighboursCoords_val + 16))->setXYZ(x, y - 1, z + 1);
	}
	else if (randValue == 1)
	{
		(*(neighboursCoords_val + 2))->setXYZ(x, y + 1, z);
		(*(neighboursCoords_val + 3))->setXYZ(x, y + 1, z - 1);
		(*(neighboursCoords_val + 4))->setXYZ(x, y + 1, z + 1);

		(*(neighboursCoords_val + 5))->setXYZ(x + 1, y + 1, z);
		(*(neighboursCoords_val + 6))->setXYZ(x + 1, y + 1, z - 1);
		(*(neighboursCoords_val + 7))->setXYZ(x + 1, y + 1, z + 1);

		(*(neighboursCoords_val + 8))->setXYZ(x + 1, y, z);
		(*(neighboursCoords_val + 9))->setXYZ(x + 1, y, z - 1);
		(*(neighboursCoords_val + 10))->setXYZ(x + 1, y, z + 1);

		(*(neighboursCoords_val + 11))->setXYZ(x + 1, y - 1, z);
		(*(neighboursCoords_val + 12))->setXYZ(x + 1, y - 1, z - 1);
		(*(neighboursCoords_val + 13))->setXYZ(x + 1, y - 1, z + 1);

		(*(neighboursCoords_val + 14))->setXYZ(x, y - 1, z);
		(*(neighboursCoords_val + 15))->setXYZ(x, y - 1, z - 1);
		(*(neighboursCoords_val + 16))->setXYZ(x, y - 1, z + 1);

	}
	else if (randValue == 2)
	{
		(*(neighboursCoords_val + 2))->setXYZ(x - 1, y, z);
		(*(neighboursCoords_val + 3))->setXYZ(x - 1, y, z - 1);
		(*(neighboursCoords_val + 4))->setXYZ(x - 1, y, z + 1);

		(*(neighboursCoords_val + 5))->setXYZ(x - 1, y - 1, z);
		(*(neighboursCoords_val + 6))->setXYZ(x - 1, y - 1, z - 1);
		(*(neighboursCoords_val + 7))->setXYZ(x - 1, y - 1, z + 1);

		(*(neighboursCoords_val + 8))->setXYZ(x, y - 1, z);
		(*(neighboursCoords_val + 9))->setXYZ(x, y - 1, z - 1);
		(*(neighboursCoords_val + 10))->setXYZ(x, y - 1, z + 1);

		(*(neighboursCoords_val + 11))->setXYZ(x + 1, y - 1, z);
		(*(neighboursCoords_val + 12))->setXYZ(x + 1, y - 1, z - 1);
		(*(neighboursCoords_val + 13))->setXYZ(x + 1, y - 1, z + 1);

		(*(neighboursCoords_val + 14))->setXYZ(x + 1, y, z);
		(*(neighboursCoords_val + 15))->setXYZ(x + 1, y, z - 1);
		(*(neighboursCoords_val + 16))->setXYZ(x + 1, y, z + 1);
	}
	else
	{
		(*(neighboursCoords_val + 2))->setXYZ(x - 1, y, z);
		(*(neighboursCoords_val + 3))->setXYZ(x - 1, y, z - 1);
		(*(neighboursCoords_val + 4))->setXYZ(x - 1, y, z + 1);

		(*(neighboursCoords_val + 5))->setXYZ(x - 1, y + 1, z);
		(*(neighboursCoords_val + 6))->setXYZ(x - 1, y + 1, z - 1);
		(*(neighboursCoords_val + 7))->setXYZ(x - 1, y + 1, z + 1);

		(*(neighboursCoords_val + 8))->setXYZ(x, y + 1, z);
		(*(neighboursCoords_val + 9))->setXYZ(x, y + 1, z - 1);
		(*(neighboursCoords_val + 10))->setXYZ(x, y + 1, z + 1);

		(*(neighboursCoords_val + 11))->setXYZ(x + 1, y + 1, z);
		(*(neighboursCoords_val + 12))->setXYZ(x + 1, y + 1, z - 1);
		(*(neighboursCoords_val + 13))->setXYZ(x + 1, y + 1, z + 1);

		(*(neighboursCoords_val + 14))->setXYZ(x + 1, y, z);
		(*(neighboursCoords_val + 15))->setXYZ(x + 1, y, z - 1);
		(*(neighboursCoords_val + 16))->setXYZ(x + 1, y, z + 1);
	}

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood3DPentagonal::getNeighborhoodType()
{
	return NeighborhoodType::Pentagonal;
}