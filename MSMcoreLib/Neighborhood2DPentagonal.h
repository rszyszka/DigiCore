#pragma once
#include "Neighborhood2D.h"
#include <random>
#include "NeighborhoodType.h"

class Neighborhood2DPentagonal : public Neighborhood2D
{
private:
	std::random_device rd;

public:
	__declspec(dllexport) Neighborhood2DPentagonal(int xSize, int ySize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType();
};