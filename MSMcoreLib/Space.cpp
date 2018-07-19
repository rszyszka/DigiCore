#include "Space.h"
#include <map>
#include "../MSMcoreLib/Neighborhood2DCircular.h"

using namespace std;

Space::Space()
{
}

Space::~Space()
{
	deleteCells();
}

Space::Space(unsigned int xSize, unsigned int ySize, unsigned int zSize, Neighborhood* neighborhood)
{
	cells = new Cell ***[xSize]; //array<Cell^,3>(xSize,ySize,zSize);

	for (unsigned int i = 0; i < xSize; i++)
	{
		cells[i] = new Cell **[ySize];
	}
	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			cells[i][j] = new Cell *[zSize];
		}
	}
	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			for (unsigned int z = 0; z < zSize; z++)
			{
				cells[i][j][z] = new Cell();
			}
		}
	}

	this->xSize = xSize;
	this->ySize = ySize;
	this->zSize = zSize;
	this->neighborhood = neighborhood;

	neighbours = new Cell*[neighborhood->getNeighboursSize()];
	for (int i = 0; i < neighborhood->getNeighboursSize(); i++)
	{
		neighbours[i] = new Cell();
	}
}

Space::Space(Space* original)
{
	this->xSize = original->xSize;
	this->ySize = original->ySize;
	this->zSize = original->zSize;
	this->cells = getCellsCopy(original);
	neighborhood = original->neighborhood;
	neighbours = original->neighbours;
}

void Space::initializeCells() const
{
	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			for (unsigned int k = 0; k < zSize; k++)
			{
				cells[i][j][k] = new Cell();
			}
		}
	}
}

void Space::deleteCells() const
{
	for (unsigned int i = 0; i < xSize; ++i)
	{
		for (unsigned int j = 0; j < ySize; ++j)
		{
			delete[] * cells[i][j];
		}
	}

	for (unsigned int i = 0; i < xSize; ++i)
	{
		delete[] * cells[i];
	}

	delete[] * cells;
}

bool Space::is3Dspace() const
{
	return xSize > 1 && ySize > 1 && zSize > 1;
}

Cell* Space::getCell(Point* p) const
{
	return cells[p->getX()][p->getY()][p->getZ()];
}

Cell**** Space::getCells() const
{
	return cells;
}

Cell**** Space::getCellsCopy(Space* originalSpace) const
{
	Cell**** copy = new Cell ***[xSize]; //array<Cell^,3>(xSize,ySize,zSize);

	for (unsigned int i = 0; i < xSize; i++)
		copy[i] = new Cell **[ySize];

	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
			copy[i][j] = new Cell *[zSize];
	}

	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			for (unsigned int k = 0; k < zSize; k++)
			{
				copy[i][j][k] = new Cell();
				Cell* orginalCell = originalSpace->cells[i][j][k];
				copy[i][j][k]->setId(orginalCell->getId());
				copy[i][j][k]->setPhase(orginalCell->getPhase());
				copy[i][j][k]->setIsBorder(orginalCell->getIsBorder());
				copy[i][j][k]->setCanGrowth(orginalCell->getCanGrowth());
				copy[i][j][k]->setBorderNeighboursIds(orginalCell->getBorderNeighboursIds());
			}
		}
	}

	return copy;
}

int Space::getXsize() const
{
	return xSize;
}

int Space::getYsize() const
{
	return ySize;
}

int Space::getZsize() const
{
	return zSize;
}

BoundaryConditions Space::getBoundaryConditions() const
{
	return neighborhood->getBoundaryConditions();
}

Neighborhood* Space::getNeighborhood() const
{
	return neighborhood;
}

int Space::getNoOfNucleons() const
{
	return noOfNucleons;
}

void Space::setNoOfNucleons(int nucleons)
{
	noOfNucleons = nucleons;
}

Cell** Space::getNeighbours(Point* p) const
{
	Point** coords = this->neighborhood->getNeighboursCoords(p);

	int neighbourhood_size = this->neighborhood->getNeighboursSize();

	for (int i = 0; i < neighbourhood_size; i++)
		neighbours[i] = getCell(*(coords + i)); //coords[i]

	return neighbours;
}

Cell** Space::getNeighbours(Neighborhood* neighborhood, Point* p) const
{
	Point** coords = neighborhood->getNeighboursCoords(p);

	int neighbourhood_size = neighborhood->getNeighboursSize();

	for (int i = 0; i < neighbourhood_size; i++)
		neighbours[i] = getCell(*(coords + i)); //coords[i]


	return neighbours;
}

int Space::getMaxId() const
{
	auto max = 0;
	for (unsigned int i = 0; i < xSize; i++)
	{
		for (unsigned int j = 0; j < ySize; j++)
		{
			for (unsigned int k = 0; k < zSize; k++)
			{
				auto id = cells[i][j][k]->getId();
				if (id > max) 
					max = id;
			}
		}
	}

	return max;
}