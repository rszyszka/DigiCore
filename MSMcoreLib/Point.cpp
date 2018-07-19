#include "Point.h"

Point::Point(void)
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Point::Point(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

int Point::getZ() const
{
	return z;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

void Point::setZ(int z)
{
	this->z = z;
}

void Point::setXYZ(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::setXY(int x, int y)
{
	this->x = x;
	this->y = y;
}