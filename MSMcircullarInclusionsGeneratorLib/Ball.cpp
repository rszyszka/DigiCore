#include "Ball.h"

Ball::Ball() : Point()
{
	this->dirX = Immovable;
	this->dirY = Immovable;
	this->dirZ = Immovable;
	this->side = false;
	this->radius = 2;
}

Ball::Ball(int x, int y, int z) : Point(x,y,z)
{
	this->dirX = Immovable;
	this->dirY = Immovable;
	this->dirZ = Immovable;
	this->side = false;
	this->radius = 2;
}

Ball::Ball(int x, int y, bool side) : Point(x,y)
{
	this->dirX = Immovable;
	this->dirY = Immovable;
	this->dirZ = Immovable;
	this->side = side;
	this->radius = 2;
}

Ball::Ball(int x, int y, bool side, int radius, Direction dirX, Direction dirY): Point(x,y)
{
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = Immovable;
	this->side = side;
	this->radius = radius;
}

Direction Ball::getDirX() const
{
	return this->dirX;
}

Direction Ball::getDirY() const
{
	return dirY;
}

Direction Ball::getDirZ() const
{
	return dirZ;
}

int Ball::getRadius() const
{
	return radius;
}

void Ball::setRadius(int radius)
{
	this->radius = radius;
}

bool Ball::isSide()
{
	return side;
}

void Ball::setDirX(Direction dirX)
{
	this->dirX = dirX;
}

void Ball::setDirY(Direction dirY)
{
	this->dirY = dirY;
}

void Ball::setDirZ(Direction dirZ)
{
	this->dirZ = dirZ;
}

void Ball::setDirXYZ(Direction dirX, Direction dirY, Direction dirZ)
{
	this->dirX = dirX;
	this->dirY = dirY;
	this->dirZ = dirZ;
}

void Ball::setDirXY(Direction dirX, Direction dirY)
{
	this->dirX = dirX;
	this->dirY = dirY;
}

void Ball::setSide(bool side)
{
	this->side = side;
}
