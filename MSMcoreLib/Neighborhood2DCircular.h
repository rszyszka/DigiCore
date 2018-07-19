#pragma once
#include "Neighborhood2D.h"
#include "NeighborhoodType.h"

class Neighborhood2DCircular : public Neighborhood2D
{
private:
	int radius;

public:
	__declspec(dllexport) Neighborhood2DCircular(int xSize, int ySize, int radius, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) NeighborhoodType getNeighborhoodType();
};