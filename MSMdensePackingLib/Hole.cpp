#include "Hole.h"

Hole::Hole(vector<BinObject*> parentObjects, Coords* coords, int r): Sphere(r), parentObjects(parentObjects)
{
	delete this->coords;
	this->coords = coords;
	this->degree = 0.0;
}

vector<BinObject*> Hole::getParentObjects()
{
	return parentObjects;
}

double Hole::getDegree()
{
	return degree;
}

void Hole::setDegree(double degree)
{
	this->degree = degree;
}
