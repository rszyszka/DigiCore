#pragma once
#include "Cell.h"

class CellSrx : public Cell
{
private:
	double	rxFraction;
	double	storedEnergy;

public:
	__declspec(dllexport) CellSrx();
	__declspec(dllexport) ~CellSrx();
	__declspec(dllexport) CellSrx(const CellSrx &original);

	__declspec(dllexport) void setStoredEnergy(double storedEnergy);
	__declspec(dllexport) void setRxFraction(double rxFraction);
	__declspec(dllexport) double getStoredEnergy() const;
	__declspec(dllexport) double getRxFraction() const;
};