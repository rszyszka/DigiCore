#include "Sphere.h"
#include "Utils.h"
#include <stdlib.h>

Sphere::Sphere(int r) : r(r)
{
    coords = Coords::coords(0, 0, 0);
    velocity = new Velocity((randomDouble() - 0.5), (randomDouble() - 0.5), (randomDouble() - 0.5));
}

int Sphere::getR()
{
    return r;
}

Coords* Sphere::getCoords()
{
    return coords;
}

void Sphere::setCoords(Coords coords)
{
    this->coords->setX(coords.getX());
    this->coords->setY(coords.getY());
    this->coords->setZ(coords.getZ());
}

Velocity* Sphere::getVelocity()
{
    return velocity;
}

void Sphere::setVelocity(Velocity velocity)
{
    this->velocity->setX(velocity.getX());
    this->velocity->setY(velocity.getY());
    this->velocity->setZ(velocity.getZ());
}
