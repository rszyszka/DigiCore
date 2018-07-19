#pragma once
#include "Cell.h"
#include "Neighborhood.h"
#include "Point.h"
#include <vector>

using namespace std;

class Space
{
private:
	Neighborhood *neighborhood;

	unsigned int xSize, ySize, zSize;

	Cell** neighbours;
	Cell**** getCellsCopy(Space *original) const;
	void initializeCells() const;
	void deleteCells() const;
	Cell ****cells; //[][][]
	int noOfNucleons = 0;

public:
	__declspec(dllexport) bool is3Dspace() const;

	__declspec(dllexport) Space();
	__declspec(dllexport) ~Space();
	__declspec(dllexport) Space(unsigned int xSize, unsigned  int ySize, unsigned  int zSize, Neighborhood *neighborhood);
	__declspec(dllexport) Space(Space *original);

	__declspec(dllexport) Cell**** getCells() const;

	__declspec(dllexport) int getXsize() const;
	__declspec(dllexport) int getYsize() const;
	__declspec(dllexport) int getZsize() const;
	__declspec(dllexport) Cell*	getCell(Point *p) const;
	__declspec(dllexport) BoundaryConditions getBoundaryConditions() const;
	__declspec(dllexport) Neighborhood* getNeighborhood() const;
	__declspec(dllexport) int getNoOfNucleons() const;
	__declspec(dllexport) void setNoOfNucleons(int nucleons);

	__declspec(dllexport) Cell** getNeighbours(Point *p) const;
	__declspec(dllexport) Cell** getNeighbours(Neighborhood *neighborhood, Point *p) const;

	__declspec(dllexport) int getMaxId() const;
};