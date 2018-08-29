#include "Volume.h"

int Volume::volumeLimitedByOneWall(int radius, int length, bool isInCube)
{
	int volume = 0;
	testOneWall++;
	if (isInCube)
		volume = volumePattern - (int)((PI * pow(length, 2)) / (double)3) * (3 * radius - length);
	else
		volume = (int)((PI * pow(length, 2)) / (double)3) * (3 * radius - length);
	return volumePattern / 2;
}

int Volume::volumeLimitedByMoreWalls(int x, int y, int z, int radius)
{
	int lengthx = x + radius >= xSize ? xSize : x + radius;
	int lengthy = y + radius >= ySize ? ySize : y + radius;
	int lengthz = z + radius >= zSize ? zSize : z + radius;
	int startx = x - radius > 0 ? 0 : x - radius;
	int starty = y - radius > 0 ? 0 : y - radius;
	int startz = z - radius > 0 ? 0 : z - radius;
	int volume = 0;
	for (int i = startx; i < lengthx; i++)
	{
		for (int j = starty; j < lengthy; j++)
		{
			for (int k = startz; k < lengthz; k++)
			{
				volume = sqrt(pow(x - i, 2) + pow(y - j, 2)
					+ pow(z - k, 2)) <= radius ? volume++ : volume;
			}
		}
	}
	return volume;
}

Volume::Volume(int radius, int sizeX, int sizeY, int sizeZ) : PI(acos(-1.0))
{
	volumePattern = (int)((4 / (double)3) * PI * pow(radius, 3));
	testMoreWalls = 0;
	testNoWall = 0;
	testOneWall = 0;
	actualVolume = 0;
}

int Volume::countVolume(int radius, int x, int y, int z)
{
	bool isIncube = true;
	int wallsCount = 0;
	if (x + radius < xSize && x - radius >= 0
		&& y + radius < ySize && y - radius >= 0
		&& z + radius < zSize && z - radius >= 0)
	{
		testNoWall++;
		actualVolume += volumePattern;
	}
	else
	{
		int height = 0;
		if (x + radius >= xSize)
		{
			wallsCount++;
			height = (radius - abs((x - xSize)));
			if (x > xSize - 1)
				isIncube = false;
		}
		if (x - radius < 0)
		{
			wallsCount++;
			height = (radius - (abs(x - 0)));
			if (x < 0)
				isIncube = false;
		}
		if (y + radius >= ySize)
		{
			wallsCount++;
			height = (radius - abs((y - ySize)));
			if (y > ySize - 1)
				isIncube = false;
		}
		if (y - radius < 0)
		{
			wallsCount++;
			height = (radius - (abs(y - 0)));
			if (y < 0)
				isIncube = false;
		}
		if (z + radius >= zSize)
		{
			wallsCount++;
			height = (radius - (abs(z - 0)));
			if (z < 0)
				isIncube = false;
		}
		if (z - radius < 0)
		{
			wallsCount++;
			height = (radius - (abs(z - 0)));
			if (z < 0)
				isIncube = false;

		}
		if (wallsCount > 1)
		{
			testMoreWalls++;
			actualVolume += volumeLimitedByMoreWalls(x, y, z, radius);
		}
		else
		{
			actualVolume += volumeLimitedByOneWall(radius, height, isIncube);
		}

	}
	return actualVolume;
}

int Volume::getActualVolume()
{
	return actualVolume;
}
