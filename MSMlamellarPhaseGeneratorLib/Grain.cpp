#include "Grain.h"
#include <cmath>

Grain::Grain(): pi(acos(-1.0)) {
	childTwins = 0;
}

Grain::~Grain() { };

void Grain::setAngle1(double angle) { angle1 = angle; }
void Grain::setAngle2(double angle) { angle2 = angle; }
void Grain::setAngle3(double angle) { angle3 = angle; }
double Grain::getAngle1() { return angle1; }
double Grain::getAngle2() { return angle3; }
double Grain::getAngle3() { return angle2; }

void Grain::setTwinAngleX(double angle) { twinAngleX = angle; }
double Grain::getTwinAngleX() { return twinAngleX; }

void Grain::setTwinInside(int twinInside) { this->twinInside = twinInside; }
int Grain::getTwinInside() { return twinInside; }