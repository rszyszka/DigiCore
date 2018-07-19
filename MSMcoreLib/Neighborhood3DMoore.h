#pragma once
#include "Neighborhood3D.h"
#include "NeighborhoodType.h"

class Neighborhood3DMoore : public Neighborhood3D
{
public:
	__declspec(dllexport) Neighborhood3DMoore(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType();
};