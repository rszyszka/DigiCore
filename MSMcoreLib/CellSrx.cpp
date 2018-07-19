#include "CellSrx.h"

CellSrx::CellSrx() : Cell()
{
	storedEnergy = 0;
	rxFraction = 0;
}

CellSrx::~CellSrx()
{
}

CellSrx::CellSrx(const CellSrx & original) : Cell(original)
{
	storedEnergy = original.storedEnergy;
	rxFraction = original.rxFraction;
}

void CellSrx::setStoredEnergy(double storedEnergy)
{
	this->storedEnergy = storedEnergy;
}

void CellSrx::setRxFraction(double rxFraction)
{
	this->rxFraction = rxFraction;
}

double CellSrx::getStoredEnergy() const
{
	return storedEnergy;
}

double CellSrx::getRxFraction() const
{
	return rxFraction;
}