#include "SpaceFiller.h"

SpaceFiller::SpaceFiller(Space* space)
{
	this->space = space;
	numberOfFilledCells = 0;
}

void SpaceFiller::fillWithAllSpheres(Bin* bin)
{
	int id = 1;
	for (Sphere* sphere : bin->getSpheres()) {
		fillWithSphere(sphere, id);
		id++;
	}
}

void SpaceFiller::fillWithSphere(Sphere* sphere, int id)
{
	int xStart = (int)floor(sphere->getCoords()->getX()) - sphere->getR();
	int xEnd = (int)ceil(sphere->getCoords()->getX()) + sphere->getR();
	int yStart = (int)floor(sphere->getCoords()->getY()) - sphere->getR();
	int yEnd = (int)ceil(sphere->getCoords()->getY()) + sphere->getR();
	int zStart = space->getZsize() == 1 ? 0 : (int)floor(sphere->getCoords()->getZ()) - sphere->getR();
	int zEnd = space->getZsize() == 1 ? 0 : (int)ceil(sphere->getCoords()->getZ()) + sphere->getR();

	for (int i = xStart; i <= xEnd && i < space->getXsize(); i++) {
		for (int j = yStart; j <= yEnd && j < space->getYsize(); j++) {
			for (int k = zStart; k <= zEnd && k < space->getZsize(); k++) {
				if (isInCircle(i, j, k, sphere)) {
					space->getCells()[i][j][k]->setId(id);
					numberOfFilledCells++;
				}
			}
		}
	}
}

int SpaceFiller::getNumberOfFilledCells()
{
	return numberOfFilledCells;
}

bool SpaceFiller::isInCircle(int x, int y, int z, Sphere* sphere)
{
	return pow(x - sphere->getCoords()->getX(), 2) + pow(y - sphere->getCoords()->getY(), 2) + pow(z - sphere->getCoords()->getZ(), 2) <= pow(sphere->getR(), 2);;
}
