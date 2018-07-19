#pragma once
#include "Neighborhood2D.h"
#include <random>
#include "NeighborhoodType.h"

class Neighborhood2DHexagonal : public Neighborhood2D
{
private:
	std::random_device rd;

public:
	__declspec(dllexport) Neighborhood2DHexagonal(int xSize, int ySize, BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual Point** neighboursCoords(Point* p);// override;
	__declspec(dllexport) NeighborhoodType getNeighborhoodType();
};