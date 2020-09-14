#pragma once
#include "Sphere.h"
#include "Bin.h"
#include "Hole.h"

bool isSphereAbleToBePlacedInBin(Sphere* sphere, Bin* bin);
bool isSphereOverlappingBin(Sphere* c1, Bin* bin);
bool isOverlappingSize(double coordsPart, int r, int size);
bool isSphereOverlappingAnyOtherSphereInBin(Sphere* sphere, Bin* bin);
bool areSpheresOverlapping(Sphere* s1, Sphere* s2);
double computeDistanceBetweenCircuits(Sphere* s1, Sphere* s2);
double computeDistanceBetweenMiddles(Sphere* s1, Sphere* s2);
double computeSquaredDistance(Coords* s1, Coords* s2);
Coords* vectorsSubtraction(Coords* c1, Coords* c2);
double norm(Coords* p);
double dot(Coords* c1, Coords* c2);
Coords* cross(Coords* c1, Coords* c2);
bool isBinObjectOneOfHolesParents(BinObject* o, Hole* h);
double randomDouble();
