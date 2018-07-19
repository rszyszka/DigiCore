#pragma once
#include "BoundaryConditions.h"
#include "Point.h"   
#include "NeighborhoodType.h"

class Neighborhood
{
protected:
	Neighborhood();
	BoundaryConditions boundaryConditions;

	int neighboursSize;
	Point** neighboursCoords_val;

public:
	__declspec(dllexport) explicit Neighborhood(BoundaryConditions boundaryConditions);
	__declspec(dllexport) virtual ~Neighborhood();

	__declspec(dllexport) BoundaryConditions getBoundaryConditions() const;
	__declspec(dllexport) virtual Point** getNeighboursCoords(Point *p) = 0;
	__declspec(dllexport) int getNeighboursSize() const;
	__declspec(dllexport) virtual NeighborhoodType getNeighborhoodType() = 0;
};
