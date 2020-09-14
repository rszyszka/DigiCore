#pragma once
#include "Hole.h"
#include "Plane.h"

class BoundaryHoleFinderHelper3D
{
public:
	BoundaryHoleFinderHelper3D(Sphere* sphere);
	vector<Hole*> determineAllPossibleHoles(Sphere* s, Plane* p1, Plane* p2);
	vector<Hole*> determineAllPossibleHoles(Plane* p, Sphere* s1, Sphere* s2);

private:
	Sphere* sphere;

	vector<Hole*> determineHolesInAxisZ(Sphere* s, Plane* p1, Plane* p2);
	vector<Hole*> determineHolesInAxisY(Sphere* s, Plane* p1, Plane* p2);
	vector<Hole*> determineHolesInAxisX(Sphere* s, Plane* p1, Plane* p2);
	vector<Hole*> determineHolesForXY(Plane* p, Sphere* s1, Sphere* s2);
	vector<Hole*> determineHolesForXZ(Plane* p, Sphere* s1, Sphere* s2);
	vector<Hole*> determineHolesForYZ(Plane* p, Sphere* s1, Sphere* s2);
};
