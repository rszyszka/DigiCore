#include "StructureAngles.h"
#include <cmath>

StructureAngles::StructureAngles(): pi(acos(-1.0)) {
	childTwins = 0;
}

StructureAngles::~StructureAngles() { };

void StructureAngles::setAngle1(double angle) { angle1 = angle; }
void StructureAngles::setAngle2(double angle) { angle2 = angle; }
void StructureAngles::setAngle3(double angle) { angle3 = angle; }
double StructureAngles::getAngle1() { return angle1; }
double StructureAngles::getAngle2() { return angle3; }
double StructureAngles::getAngle3() { return angle2; }

void StructureAngles::setTwinAngleX(double angle) { twinAngleX = angle; }
double StructureAngles::getTwinAngleX() { return twinAngleX; }

void StructureAngles::setTwinInside(int twinInside) { this->twinInside = twinInside; }
int StructureAngles::getTwinInside() { return twinInside; }