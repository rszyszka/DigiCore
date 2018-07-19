#pragma once
#include "Neighborhood2D.h"
#include "NeighborhoodType.h"

class Neighborhood2DVonNeumann : public Neighborhood2D
{
public:
	__declspec(dllexport) Neighborhood2DVonNeumann(int xSize, int ySize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType();
};