#pragma once
#include <vector>
#include "Plane.h"

using namespace std;

class Bin
{
public:
	__declspec(dllexport) Bin(int xSize, int ySize, int zSize);
	bool addSphere(Sphere* sphere);
	int getNumberOfCirclesPacked();
	int getXSize();
	int getYSize();
	int getZSize();
	vector<Sphere*> getSpheres();
	vector<Plane*> getPlanes();

private:
	const int xSize, ySize, zSize;
	vector<Plane*> planes;
	vector<Sphere*> spheres;
	void addAllBinPlanes();
};
