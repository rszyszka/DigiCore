#include "Cell.h"

Cell::Cell()
{
	this->phase = Phase(None);
	this->id = 0;
	this->isBorder;
	this->canGrowth;
	this->borderNeighboursIds = std::make_tuple(0, 0);
}

Cell::~Cell()
{

}

Cell::Cell(const Cell &original)
{
	this->id = original.id;
	this->phase = original.phase;
	this->isBorder = original.isBorder;
	this->canGrowth = original.canGrowth;
	this->borderNeighboursIds = original.borderNeighboursIds;
}

void Cell::setId(int id)
{
	this->id = id;
}

void Cell::setPhase(Phase phase)
{
	this->phase = phase;
}

void Cell::setIsBorder(bool isBorder)
{
	this->isBorder = isBorder;
}

void Cell::setCanGrowth(bool canGrowth)
{
	this->canGrowth = canGrowth;
}

int	Cell::getId() const
{
	return this->id;
}

Phase Cell::getPhase() const
{
	return this->phase;
}

bool Cell::getIsBorder() const
{
	return this->isBorder;
}

bool Cell::getCanGrowth() const
{
	return this->canGrowth;
}

void Cell::setPropertiesFromOtherCell(Cell* cell)
{
	this->id = cell->id;
	this->phase = cell->phase;
	this->isBorder = cell->isBorder;
	this->canGrowth = cell->canGrowth;
	this->borderNeighboursIds = cell->borderNeighboursIds;
}

void Cell::setBorderNeighboursIds(std::tuple<int, int> borderNeighboursIds)
{
	this->borderNeighboursIds = borderNeighboursIds;
}

std::tuple<int, int> Cell::getBorderNeighboursIds() const
{
	return this->borderNeighboursIds;
}

int Cell::getFirstBorderNeighbourId()
{
	return std::get<0>(this->borderNeighboursIds);
}

int Cell::getSecondBorderNeighbourId()
{
	return std::get<1>(this->borderNeighboursIds);
}