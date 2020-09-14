#pragma once
#include "MinDistance.h"
#include "Bin.h"
class ForEachMinDistance : public MinDistance
{
public:
	ForEachMinDistance(Bin* bin);
	double compute(Hole* hole) override;

private:
	Bin* bin;
	double determineMinDistanceToPlanes(Hole* hole);
};

