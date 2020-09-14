#pragma once
#include "HolesFinder.h"
#include "BoundaryHoleFinderHelper3D.h"

class HolesFinder3D : public HolesFinder
{
public:
	HolesFinder3D(Bin* bin);

protected:
	void determineCornerHolesIfExist() override;
	void determineBoundaryHolesIfExists() override;
	void determineHolesFromSpheresIfExist() override;

private:
	BoundaryHoleFinderHelper3D* helper;

	void determineTwoPlanesAndSphereBoundaryHoles();
	void determineNextBoundaryHole(Sphere* s, Plane* p1, Plane* p2);
	void determinePlaneAndTwoSpheresBoundaryHoles();
	void determineNextBoundaryHole(Plane* p, Sphere* s1, Sphere* s2);
	void determineNextHoleIfExist(Sphere* s1, Sphere* s2, Sphere* s3);
	vector<Hole*> determineAllPossibleHoles(Sphere* s1, Sphere* s2, Sphere* s3);
};

