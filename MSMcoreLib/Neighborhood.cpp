#include "Neighborhood.h"

Neighborhood::Neighborhood()
{

}
Neighborhood::~Neighborhood()
{
	delete[] * neighboursCoords_val;
}

Neighborhood::Neighborhood(BoundaryConditions boundaryConditions)
{
	this->boundaryConditions = boundaryConditions;
}

BoundaryConditions Neighborhood::getBoundaryConditions() const
{
	return boundaryConditions;
}
int Neighborhood::getNeighboursSize(void) const
{
	return neighboursSize;
}