#pragma once
#include "Neighborhood.h"
#include "NeighborhoodType.h"

class Neighborhood2D : public Neighborhood
{
private:
	int xSize, ySize;

public:
	__declspec(dllexport) Neighborhood2D(int xSize, int ySize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) Point** getNeighboursCoords(Point* p);
	__declspec(dllexport) virtual Point** neighboursCoords(Point *p) = 0;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType() = 0;
};