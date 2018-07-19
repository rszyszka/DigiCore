#pragma once
#include "Neighborhood3D.h"
#include <random>
#include "NeighborhoodType.h"

class Neighborhood3DPentagonal : public Neighborhood3D
{
private:
	std::random_device rd;

public:
	__declspec(dllexport) Neighborhood3DPentagonal(int xSize, int ySize, int zSize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType();
};