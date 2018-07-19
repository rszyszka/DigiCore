#pragma once
#include "Neighborhood3D.h"
#include "NeighborhoodType.h"

class Neighborhood3DVonNeumann : public Neighborhood3D
{
public:
	__declspec(dllexport) Neighborhood3DVonNeumann(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType();
};