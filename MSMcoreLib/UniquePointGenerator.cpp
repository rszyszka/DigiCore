#include "UniquePointGenerator.h"
#include <random>

UniquePointGenerator::UniquePointGenerator(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax)
{
	X_MIN = xMin;
	X_MAX = xMax;
	Y_MIN = yMin;
	Y_MAX = yMax;
	Z_MIN = zMin;
	Z_MAX = zMax;
	MAX_pointS = (X_MAX - X_MIN + 1) * (Y_MAX - Y_MIN + 1) * (Z_MAX - Z_MIN + 1);

	points = new Point*[MAX_pointS];
	head = MAX_pointS;
	initializePoints();
}


void UniquePointGenerator::initializePoints() const
{
	int pointer = 0;
	for (int i = X_MIN; i <= X_MAX; i++)
	{
		for (int j = Y_MIN; j <= Y_MAX; j++)
		{
			for (int k = Z_MIN; k <= Z_MAX; k++)
				points[pointer++] = new Point(i, j, k);
		}
	}
}

Point* UniquePointGenerator::nextPoint()
{
	if (counter == MAX_pointS)
		return nullptr;
	counter++;

	std::uniform_int_distribution<int> dist(0, head - 1);
	int index = dist(rd);
	Point* tmp = points[index];
	points[index] = points[head - 1];
	points[head - 1] = nullptr;
	head--;

	return tmp;
}

void UniquePointGenerator::reset()
{
	counter = 0;
	head = MAX_pointS;
	initializePoints();
}