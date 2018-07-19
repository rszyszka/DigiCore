#include "Neighborhood3DVonNeumann.h"

Neighborhood3DVonNeumann::Neighborhood3DVonNeumann(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions) : Neighborhood3D(xSize, ySize, zSize, boundaryConditions)
{
	neighboursSize = 6;
	neighboursCoords_val = new Point*[neighboursSize];
	for (int i = 0; i < neighboursSize; i++)
		neighboursCoords_val[i] = new Point(0, 0, 0);
}

Point** Neighborhood3DVonNeumann::neighboursCoords(Point* p)
{
	int x = p->getX();
	int y = p->getY();
	int z = p->getZ();

	(*neighboursCoords_val)->setXYZ(x + 1, y, z);
	(*(neighboursCoords_val + 1))->setXYZ(x - 1, y, z);
	(*(neighboursCoords_val + 2))->setXYZ(x, y + 1, z);
	(*(neighboursCoords_val + 3))->setXYZ(x, y - 1, z);
	(*(neighboursCoords_val + 4))->setXYZ(x, y, z - 1);
	(*(neighboursCoords_val + 5))->setXYZ(x, y, z + 1);

	return neighboursCoords_val;
}


NeighborhoodType Neighborhood3DVonNeumann::getNeighborhoodType()
{
	return NeighborhoodType::VonNeumann;
}