#pragma once
#include <math.h>

class Volume 
{
private:
	int xSize;
	int ySize;
	int zSize;
	int testNoWall;
	int testMoreWalls;
	int testOneWall;
	int actualVolume;

	const double PI;
	int volumePattern;

	int volumeLimitedByOneWall(int radius, int length, bool isInCube);
	int volumeLimitedByMoreWalls(int x, int y, int z, int radius);

public:
	__declspec(dllexport) Volume(int radius, int sizeX, int sizeY, int sizeZ);
	__declspec(dllexport) int countVolume(int radius, int x, int y, int z);
	__declspec(dllexport) int getActualVolume();
};