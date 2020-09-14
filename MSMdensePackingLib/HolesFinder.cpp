#include "HolesFinder.h"
#include "HolesFinder3D.h"
#include "HolesFinder2D.h"
#include "ForEachMinDistance.h"
#include "Utils.h"


double HolesFinder::PENALTY_VALUE = 0.2;
PenaltyType HolesFinder::penaltyType = PenaltyType::GLOBAL;


HolesFinder* HolesFinder::create(Bin* bin)
{
	if (bin->getZSize() > 1) {
		return new HolesFinder3D(bin);
	}
	else {
		return new HolesFinder2D(bin);
	}
}

Hole* HolesFinder::findHoleWithMaximumDegree()
{
	auto size = solutionHoles.size();
	Hole* holeWithMaximumDegree = solutionHoles.at(0);
	for (int i = 1; i < size; i++) {
		Hole* hole = solutionHoles.at(i);
		if (hole->getDegree() > holeWithMaximumDegree->getDegree()) {
			holeWithMaximumDegree = hole;
		}
	}
	return holeWithMaximumDegree;
}

vector<Hole*> HolesFinder::findForSphere(Sphere* sphere)
{
	this->sphere = sphere;
	clearSolutionHoles();
	determineCornerHolesIfExist();
	determineBoundaryHolesIfExists();
	determineHolesFromSpheresIfExist();
	return solutionHoles;
}

HolesFinder::HolesFinder(Bin* bin)
{
	this->sphere = nullptr;
	this->bin = bin;
	minDistance = new ForEachMinDistance(bin);
}

bool HolesFinder::possibleCoordsFromSpheresExist(Sphere* s1, Sphere* s2)
{
	return 2 * sphere->getR() >= computeDistanceBetweenCircuits(s1, s2);
}

bool HolesFinder::possibleBoundaryCoordsExist(Plane* p, Sphere* s)
{
	return 2 * sphere->getR() >= p->computeDistance(s);
}

void HolesFinder::addNotOverlappingHolesToSolutionHolesList(vector<Hole*> possibleHoles)
{
	for (Hole* possibleHole : possibleHoles) {
		createAndAddSolutionHoleIfSphereCoordsValid(possibleHole);
	}
}

Coords* HolesFinder::determineAuxiliaryCoords(Sphere* s1, Sphere* s2, double distanceBetweenMiddles)
{
	int r1 = sphere->getR() + s1->getR();
	double auxiliaryX = r1 * (s2->getCoords()->getX() - s1->getCoords()->getX()) / distanceBetweenMiddles;
	double auxiliaryY = r1 * (s2->getCoords()->getY() - s1->getCoords()->getY()) / distanceBetweenMiddles;
	double auxiliaryZ = r1 * (s2->getCoords()->getZ() - s1->getCoords()->getZ()) / distanceBetweenMiddles;
	return Coords::coords(auxiliaryX, auxiliaryY, auxiliaryZ);
}

double HolesFinder::determineCosA(Sphere* c1, Sphere* c2, double distanceBetweenMiddles)
{
	int r1 = sphere->getR() + c1->getR();
	int r2 = sphere->getR() + c2->getR();
	return (pow(distanceBetweenMiddles, 2) + pow(r1, 2) - pow(r2, 2)) / (2 * distanceBetweenMiddles * r1);
}

void HolesFinder::createAndAddSolutionHoleIfSphereCoordsValid(Hole* possibleHole)
{
	Sphere* testSphere = new Sphere(sphere->getR());
	testSphere->setCoords(*possibleHole->getCoords());
	if (isSphereAbleToBePlacedInBin(testSphere, bin)) {
		calculateHoleDegree(possibleHole);
		solutionHoles.push_back(possibleHole);
	}
	delete testSphere;
}

void HolesFinder::calculateHoleDegree(Hole* hole)
{
	bool penalty = determineIfPenaltyShouldBeApplied(hole);
	double degree = 1.0 - (minDistance->compute(hole) / sphere->getR());
	hole->setDegree(penalty ? degree - PENALTY_VALUE : degree);
}

bool HolesFinder::determineIfPenaltyShouldBeApplied(Hole* hole)
{
	switch (penaltyType) {
	case PenaltyType::GLOBAL:
		for (BinObject* o : hole->getParentObjects()) {
			if (Plane* p = dynamic_cast<Plane*>(o)) {
				return true;
			}
		}
		break;
	case PenaltyType::ALL_EXCEPT_TOP:
		for (BinObject* o : hole->getParentObjects()) {
			Plane* p = dynamic_cast<Plane*>(o);
			if (p != nullptr && (p->getPosition() != 0 || p->getType() != Plane::Type::XZ)) {
				return true;
			}
		}
		break;
	case PenaltyType::ALL_EXCEPT_BOT:
		for (BinObject* o : hole->getParentObjects()) {
			Plane* p = dynamic_cast<Plane*>(o);
			if (p != nullptr &&  (p->getPosition() != 100 || p->getType() != Plane::Type::XZ)) {
				return true;
			}
		}
		break;
	}
	return false;
}

void HolesFinder::clearSolutionHoles()
{
	auto length = solutionHoles.size();
	for (size_t i = 0; i < length; i++)
	{
		delete solutionHoles.back();
		solutionHoles.pop_back();
	}
}
