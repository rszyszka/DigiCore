#include "Coords.h"
#include <iostream>

Coords::Coords(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Coords* Coords::coords(double x, double y)
{
	return new Coords(x, y, 0);
}

Coords* Coords::coords(double x, double y, double z)
{
	return new Coords(isnan(x) ? 0 : x, isnan(y) ? 0 : y, isnan(z) ? 0 : z);
}

double Coords::getX()
{
	return x;
}

double Coords::getY()
{
	return y;
}

double Coords::getZ()
{
	return z;
}

void Coords::setX(double x)
{
	this->x = x;
}

void Coords::setY(double y)
{
	this->y = y;
}

void Coords::setZ(double z)
{
	this->z = z;
}

bool Coords::operator==(const Coords o) const
{
	return x == o.x &&
		y == o.y &&
		z == o.z;
}
