#include "HolesFinder2D.h"
#include "Utils.h"

HolesFinder2D::HolesFinder2D(Bin* bin) : HolesFinder(bin)
{
}

void HolesFinder2D::determineCornerHolesIfExist()
{
    Plane* yz1 = bin->getPlanes().at(0);
    Plane* yz2 = bin->getPlanes().at(1);
    Plane* xz1 = bin->getPlanes().at(2);
    Plane* xz2 = bin->getPlanes().at(3);
    int x1 = sphere->getR();
    int y1 = sphere->getR();
    int x2 = bin->getXSize() - x1;
    int y2 = bin->getYSize() - y1;

    vector<Hole*> possibleHoles;
    possibleHoles.push_back(new Hole({ yz1, xz1 }, Coords::coords(x1, y1), sphere->getR()));
    possibleHoles.push_back(new Hole({ yz2, xz1 }, Coords::coords(x2, y1), sphere->getR()));
    possibleHoles.push_back(new Hole({ yz1, xz2 }, Coords::coords(x1, y2), sphere->getR()));
    possibleHoles.push_back(new Hole({ yz2, xz2 }, Coords::coords(x2, y2), sphere->getR()));

    addNotOverlappingHolesToSolutionHolesList(possibleHoles);
}

void HolesFinder2D::determineBoundaryHolesIfExists()
{
    for (Plane* p : bin->getPlanes()) {
        for (Sphere* s : bin->getSpheres()) {
            if (possibleBoundaryCoordsExist(p, s)) {
                determineNextBoundaryHole(p, s);
            }
        }
    }
}

void HolesFinder2D::determineHolesFromSpheresIfExist()
{
    int numberOfSpheresInBin = (int) bin->getSpheres().size();
    for (int i = 0; i < numberOfSpheresInBin - 1; i++) {
        Sphere* s1 = bin->getSpheres().at(i);
        for (int j = i + 1; j < numberOfSpheresInBin; j++) {
            Sphere* s2 = bin->getSpheres().at(j);
            determineNextHoleFromSpheresIfExist(s1, s2);
        }
    }
}

void HolesFinder2D::determineNextBoundaryHole(Plane* p, Sphere* s)
{
    vector<Hole*> possibleHoles;
    int r1 = sphere->getR();
    int r2 = s->getR();
    if (p->getType() == Plane::Type::XZ) {
        double y = abs(r1 - p->getPosition());
        double sqrtValue = sqrt(pow(r1 + r2, 2) - pow(y - s->getCoords()->getY(), 2));
        double x1 = sqrtValue + s->getCoords()->getX();
        double x2 = -sqrtValue + s->getCoords()->getX();
        possibleHoles.push_back(new Hole({ p, s }, Coords::coords(x1, y), sphere->getR()));
        possibleHoles.push_back(new Hole({ p, s }, Coords::coords(x2, y), sphere->getR()));
    }
    else {
        double x = abs(r1 - p->getPosition());
        double sqrtValue = sqrt(pow(r1 + r2, 2) - pow(x - s->getCoords()->getX(), 2));
        double y1 = sqrtValue + s->getCoords()->getY();
        double y2 = -sqrtValue + s->getCoords()->getY();
        possibleHoles.push_back(new Hole({ p, s }, Coords::coords(x, y1), sphere->getR()));
        possibleHoles.push_back(new Hole({ p, s }, Coords::coords(x, y2), sphere->getR()));
    }
    addNotOverlappingHolesToSolutionHolesList(possibleHoles);
}

void HolesFinder2D::determineNextHoleFromSpheresIfExist(Sphere* s1, Sphere* s2)
{
    if (possibleCoordsFromSpheresExist(s1, s2)) {
        vector<Hole*> possibleHoles = determineAllPossibleHoles(s1, s2);
        addNotOverlappingHolesToSolutionHolesList(possibleHoles);
    }
}

vector<Hole*> HolesFinder2D::determineAllPossibleHoles(Sphere* s1, Sphere* s2)
{
    double distanceBetweenMiddles = computeDistanceBetweenMiddles(s1, s2);
    Coords* auxiliaryCoords = determineAuxiliaryCoords(s1, s2, distanceBetweenMiddles);
    double cosA = determineCosA(s1, s2, distanceBetweenMiddles);
    double sinA = sqrt(1 - pow(cosA, 2));

    double x1 = auxiliaryCoords->getX() * cosA - auxiliaryCoords->getY() * sinA + s1->getCoords()->getX();
    double y1 = auxiliaryCoords->getX() * sinA + auxiliaryCoords->getY() * cosA + s1->getCoords()->getY();
    double x2 = auxiliaryCoords->getX() * cosA + auxiliaryCoords->getY() * sinA + s1->getCoords()->getX();
    double y2 = auxiliaryCoords->getX() * -sinA + auxiliaryCoords->getY() * cosA + s1->getCoords()->getY();

    delete auxiliaryCoords;

    vector<Hole*> possibleHoles;
    possibleHoles.push_back(new Hole({ s1, s2 }, Coords::coords(x1, y1), sphere->getR()));
    possibleHoles.push_back(new Hole({ s1, s2 }, Coords::coords(x2, y2), sphere->getR()));

    return possibleHoles;
}
