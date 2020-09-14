#pragma once
#include "Sphere.h"
#include <vector>

using namespace std;

class Hole : public Sphere
{
public:
	Hole(vector<BinObject*> parentObjects, Coords* coords, int r);
	vector<BinObject*> getParentObjects();
	double getDegree();
	void setDegree(double degree);

private:
	vector<BinObject*> parentObjects;
	double degree;
};
