#pragma once
#include "HolesFinder.h"

class HolesFinder2D : public HolesFinder
{
public:
	HolesFinder2D(Bin* bin);

protected:
	void determineCornerHolesIfExist() override;
	void determineBoundaryHolesIfExists() override;
	void determineHolesFromSpheresIfExist() override;

private:
	void determineNextBoundaryHole(Plane* p, Sphere* s);
	void determineNextHoleFromSpheresIfExist(Sphere* s1, Sphere* s2);
	vector<Hole*> determineAllPossibleHoles(Sphere* s1, Sphere* s2);
};
