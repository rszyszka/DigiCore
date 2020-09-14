#include "Velocity.h"

Velocity::Velocity(double x, double y) : Coords(x, y, 0)
{
}

Velocity::Velocity(double x, double y, double z) : Coords(x, y, z)
{
}

void Velocity::negateX()
{
	setX(-getX());
}

void Velocity::negateY()
{
	setY(-getY());
}

void Velocity::negateZ()
{
	setZ(-getZ());
}

void Velocity::addToX(double value)
{
	setX(getX() + value);
}

void Velocity::addToY(double value)
{
	setY(getY() + value);
}

void Velocity::addToZ(double value)
{
	setZ(getZ() + value);
}

void Velocity::multiplyX(double value)
{
	setX(getX() * value);
}

void Velocity::multiplyY(double value)
{
	setY(getY() * value);
}

void Velocity::multiplyZ(double value)
{
	setZ(getZ() * value);
}
