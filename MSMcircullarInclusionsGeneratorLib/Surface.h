#pragma once
#include <math.h>

class Surface
{
private:
	int xSize;
	int ySize;
	int maxArea;
	int maxRadius;

	const double PI;
public:
	__declspec(dllexport) Surface(int radius, int xSize, int ySize);
	__declspec(dllexport) int countMaxArea(int x, int y);
	__declspec(dllexport) int countArea(int x, int y, int radius);
	__declspec(dllexport) int countNotRoundArea(int x, int y, int radius);
	__declspec(dllexport) int areaLimitedByOneBorder(int x, int y, int radius);
	__declspec(dllexport) int areaLimitedByTwoBorders(int x, int y, int radius);

};