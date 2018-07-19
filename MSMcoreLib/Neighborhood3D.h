#pragma once
#include "Neighborhood.h"
#include "NeighborhoodType.h"

class Neighborhood3D : public Neighborhood
{
private:
	int xSize, ySize, zSize;

public:
	__declspec(dllexport) Neighborhood3D(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) Point** getNeighboursCoords(Point* p);
	__declspec(dllexport) virtual Point** neighboursCoords(Point *p) = 0;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType() = 0;
};