#include "Grain.h"

Grain::Grain(vector<Point*> p, int id)
{
	this->id = id;
	this->points = p;
}

int Grain::getId()
{
	return id;
}

vector<Point*> Grain::getPoints()
{
	return points;
}