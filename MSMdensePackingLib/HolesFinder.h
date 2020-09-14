#pragma once
#include "Hole.h"
#include "Bin.h"
#include "PenaltyType.h"
#include "MinDistance.h"

class HolesFinder
{
public:
    __declspec(dllexport) static double PENALTY_VALUE;
    __declspec(dllexport) static PenaltyType penaltyType;

     __declspec(dllexport) static HolesFinder* create(Bin* bin);
     Hole* findHoleWithMaximumDegree();
     vector<Hole*> findForSphere(Sphere* sphere);

protected:
     Bin* bin;
     Sphere* sphere;
     vector<Hole*> solutionHoles;
     MinDistance* minDistance;

     HolesFinder(Bin* bin);
     bool possibleCoordsFromSpheresExist(Sphere* s1, Sphere* s2);
     bool possibleBoundaryCoordsExist(Plane* p, Sphere* s);
     void addNotOverlappingHolesToSolutionHolesList(vector<Hole*> possibleHoles);
     virtual void determineCornerHolesIfExist() =0;
     virtual void determineBoundaryHolesIfExists() =0;
     virtual void determineHolesFromSpheresIfExist()=0;
     Coords* determineAuxiliaryCoords(Sphere* s1, Sphere* s2, double distanceBetweenMiddles);
     double determineCosA(Sphere* c1, Sphere* c2, double distanceBetweenMiddles);


private:
     void createAndAddSolutionHoleIfSphereCoordsValid(Hole* possibleHole);
     void calculateHoleDegree(Hole* hole);
     bool determineIfPenaltyShouldBeApplied(Hole* hole);
     void clearSolutionHoles();
};

