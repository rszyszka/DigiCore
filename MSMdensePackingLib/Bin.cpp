#include "Bin.h"
#include "Utils.h"

void Bin::addAllBinPlanes()
{
	planes.push_back(new Plane(Plane::Type::YZ, 0));
	planes.push_back(new Plane(Plane::Type::YZ, xSize));
	planes.push_back(new Plane(Plane::Type::XZ, 0));
	planes.push_back(new Plane(Plane::Type::XZ, ySize));
	if (zSize > 1) {
		planes.push_back(new Plane(Plane::Type::XY, 0));
		planes.push_back(new Plane(Plane::Type::XY, zSize));
	}
}

Bin::Bin(int xSize, int ySize, int zSize) : xSize(xSize), ySize(ySize), zSize(zSize)
{
	addAllBinPlanes();
}

bool Bin::addSphere(Sphere* sphere)
{
	if (isSphereAbleToBePlacedInBin(sphere, this)) {
		spheres.push_back(sphere);
		return true;
	}
	return false;
}

int Bin::getNumberOfCirclesPacked()
{
	return (int) spheres.size();
}

int Bin::getXSize()
{
	return xSize;
}

int Bin::getYSize()
{
	return ySize;
}

int Bin::getZSize()
{
	return zSize;
}

vector<Sphere*> Bin::getSpheres()
{
	return spheres;
}

vector<Plane*> Bin::getPlanes()
{
	return planes;
}
