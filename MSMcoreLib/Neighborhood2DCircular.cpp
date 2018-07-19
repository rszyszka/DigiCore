#include "Neighborhood2DCircular.h"
#include <math.h>

Neighborhood2DCircular::Neighborhood2DCircular(int xSize, int ySize, int radius, BoundaryConditions boundaryConditions) : Neighborhood2D(xSize, ySize, boundaryConditions)
{
	this->radius = radius;
	int count = 0;

	for (int j = 0; j < 2 * radius - 1; j++)
	{ //y
		for (int k = 0; k < 2 * radius - 1; k++)
		{ //x
			int x = radius - 1 - k;
			int y = radius - 1 - j;

			double distance = sqrt(static_cast<double>((x * x) + (y * y)));
			if (distance <= radius - 1)
				count++;
		}
	}
	count -= 1;

	neighboursCoords_val = new Point*[count];

	for (int i = 0; i < count; i++)
		neighboursCoords_val[i] = new Point(0, 0);

	neighboursSize = count;
}

Point** Neighborhood2DCircular::neighboursCoords(Point* p)
{
	int head = 0;
	int startX = p->getX() - (radius - 1);
	int startY = p->getY() - (radius - 1);

	for (int j = 0; j < 2 * radius - 1; j++)
	{ //y
		for (int k = 0; k < 2 * radius - 1; k++)
		{ //x
			int x = startX + k;
			int y = startY + j;

			int check_x = radius - 1 - k;
			int check_y = radius - 1 - j;

			if (x == p->getX() && y == p->getY())
				continue;

			if(x < 0 || y < 0)	
				auto b = x;

			double distance = sqrt(static_cast<double>((check_x * check_x) + (check_y * check_y)));
			if (distance <= radius - 1)
				neighboursCoords_val[head++]->setXY(x, y);
		}
	}

	return neighboursCoords_val;
}

NeighborhoodType Neighborhood2DCircular::getNeighborhoodType()
{
	return NeighborhoodType::Circular;
}
