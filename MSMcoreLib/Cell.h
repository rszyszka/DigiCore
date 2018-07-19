#pragma once
#include "Phase.h"
#include <tuple>

class Cell
{
protected:
	Phase phase;
	int id = 0;
	bool isBorder = false;
	bool canGrowth = true;
	std::tuple<int, int> borderNeighboursIds;

public:
	__declspec(dllexport) Cell();
	__declspec(dllexport) ~Cell();
	__declspec(dllexport) Cell(const Cell& original);

	__declspec(dllexport) void setId(int id);
	__declspec(dllexport) void setPhase(Phase phase);
	__declspec(dllexport) int getId() const;
	__declspec(dllexport) Phase getPhase() const;
	__declspec(dllexport) bool getIsBorder() const;
	__declspec(dllexport) void setIsBorder(bool isBorder);
	__declspec(dllexport) bool getCanGrowth() const;
	__declspec(dllexport) void setCanGrowth(bool canGrowth);
	__declspec(dllexport) void setPropertiesFromOtherCell(Cell* cell);
	__declspec(dllexport) void setBorderNeighboursIds(std::tuple<int, int> borderNeighboursIds);
	__declspec(dllexport) std::tuple<int, int> getBorderNeighboursIds() const;
	__declspec(dllexport) int getFirstBorderNeighbourId();
	__declspec(dllexport) int getSecondBorderNeighbourId();
};