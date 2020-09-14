#include "Utils.h"
#include <time.h>

bool isSphereAbleToBePlacedInBin(Sphere* sphere, Bin* bin)
{
    return !(isSphereOverlappingBin(sphere, bin) || isSphereOverlappingAnyOtherSphereInBin(sphere, bin));
}

bool isSphereOverlappingBin(Sphere* c1, Bin* bin)
{
    bool overlappingWidth = isOverlappingSize(c1->getCoords()->getX(), c1->getR(), bin->getXSize());
    bool overlappingHeight = isOverlappingSize(c1->getCoords()->getY(), c1->getR(), bin->getYSize());
    bool overlappingDepth = bin->getZSize() > 1 && isOverlappingSize(c1->getCoords()->getZ(), c1->getR(), bin->getZSize());

    return overlappingWidth || overlappingHeight || overlappingDepth;
}

bool isOverlappingSize(double coordsPart, int r, int size)
{
    return coordsPart - r < 0 || coordsPart + r > size;
}

bool isSphereOverlappingAnyOtherSphereInBin(Sphere* sphere, Bin* bin)
{
    for (Sphere* s : bin->getSpheres()) {
        if (sphere == s) {
            continue;
        }
        if (areSpheresOverlapping(sphere, s)) {
            return true;
        }
    }
    return false;
}

bool areSpheresOverlapping(Sphere* s1, Sphere* s2)
{
    return computeDistanceBetweenCircuits(s1, s2) < 0;
}

double computeDistanceBetweenCircuits(Sphere* s1, Sphere* s2)
{
    return computeDistanceBetweenMiddles(s1, s2) - s1->getR() - s2->getR();
}

double computeDistanceBetweenMiddles(Sphere* s1, Sphere* s2)
{
    return sqrt(computeSquaredDistance(s1->getCoords(), s2->getCoords()));
}

double computeSquaredDistance(Coords* s1, Coords* s2)
{
    return pow(s1->getX() - s2->getX(), 2) + pow(s1->getY() - s2->getY(), 2) + pow(s1->getZ() - s2->getZ(), 2);
}

Coords* vectorsSubtraction(Coords* c1, Coords* c2)
{
    return Coords::coords(c1->getX() - c2->getX(), c1->getY() - c2->getY(), c1->getZ() - c2->getZ());
}

double norm(Coords* p)
{
    return sqrt(pow(p->getX(), 2) + pow(p->getY(), 2) + pow(p->getZ(), 2));
}

double dot(Coords* c1, Coords* c2)
{
    return c1->getX() * c2->getX() + c1->getY() * c2->getY() + c1->getZ() * c2->getZ();
}

Coords* cross(Coords* c1, Coords* c2)
{
    double x = c1->getY() * c2->getZ() - c1->getZ() * c2->getY();
    double y = c1->getZ() * c2->getX() - c1->getX() * c2->getZ();
    double z = c1->getX() * c2->getY() - c1->getY() * c2->getX();
    return Coords::coords(x, y, z);
}

bool isBinObjectOneOfHolesParents(BinObject* o, Hole* h)
{
    vector<BinObject*> parentObjects = h->getParentObjects();
    return find(parentObjects.begin(), parentObjects.end(), o) != parentObjects.end();
}

double randomDouble()
{
    return (rand() % 1000) / 1000.0;
}
