#pragma once
#include "Point.h"
#include <random>

class UniquePointGenerator
{
private:
	std::random_device rd;

	Point** points;
	int X_MIN, X_MAX, Y_MIN, Y_MAX, Z_MIN, Z_MAX, MAX_pointS;
	int counter, head;

public:
	__declspec(dllexport) UniquePointGenerator(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax);

	__declspec(dllexport) void initializePoints() const;
	__declspec(dllexport) Point* nextPoint();
	__declspec(dllexport) void reset();
};