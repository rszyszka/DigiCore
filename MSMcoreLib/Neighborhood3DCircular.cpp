#include "Neighborhood3DCircular.h"
#include <cmath>

Neighborhood3DCircular::Neighborhood3DCircular(int xSize, int ySize, int zSize, int radius, BoundaryConditions boundaryConditions) : Neighborhood3D(xSize, ySize, zSize, boundaryConditions)
{
	this->radius = radius;
	int count = 0;

	for (int i = 0; i < 2 * radius - 1; i++)
	{ //z
		for (int j = 0; j < 2 * radius - 1; j++)
		{ //y
			for (int k = 0; k < 2 * radius - 1; k++)
			{ //x
				int x = radius - 1 - k;
				int y = radius - 1 - j;
				int z = radius - 1 - i;

				double distance = sqrt(static_cast<double>(x * x + y * y + z * z));
				if (distance <= radius - 1)
					count++;
			}
		}
	}
	count -= 1;

	neighboursCoords_val = new Point*[count];

	for (int i = 0; i < count; i++)
		neighboursCoords_val[i] = new Point(0, 0);

	neighboursSize = count;
}

Point** Neighborhood3DCircular::neighboursCoords(Point* p)
{
	int head = 0;
	int startX = p->getX() - (radius - 1);
	int startY = p->getY() - (radius - 1);
	int startZ = p->getZ() - (radius - 1);

	for (int i = 0; i < 2 * radius - 1; i++)
	{ //z
		for (int j = 0; j < 2 * radius - 1; j++)
		{ //y
			for (int k = 0; k < 2 * radius - 1; k++)
			{ //x
				int x = startX + k;
				int y = startY + j;

				int check_x = radius - 1 - k;
				int check_y = radius - 1 - j;
				int z = startZ + i;
				if (x == p->getX() && y == p->getY() && z == p->getZ())
					continue;

				double distance = sqrt(static_cast<double>(check_x * check_x + check_y * check_y));
				if (distance <= radius - 1)
					neighboursCoords_val[head++]->setXY(x, y);
			}
		}
	}

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood3DCircular::getNeighborhoodType()
{
	return NeighborhoodType::Circular;
}