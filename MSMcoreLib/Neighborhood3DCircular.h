#pragma once
#include "Neighborhood3D.h"
#include "NeighborhoodType.h"

class Neighborhood3DCircular : public Neighborhood3D
{
private:
	int radius;

public:
	__declspec(dllexport) Neighborhood3DCircular(int xSize, int ySize, int zSize, int radius, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType();
};