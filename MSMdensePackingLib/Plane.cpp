#include "Plane.h"
#include <math.h>

Plane::Plane(Type type, double position): type(type), position(position)
{
}

double Plane::computeDistance(Sphere* s)
{
    switch (type) {
    case Type::YZ:
        return fabs(s->getCoords()->getX() - position) - s->getR();
    case Type::XZ:
        return fabs(s->getCoords()->getY() - position) - s->getR();
    default:
        return fabs(s->getCoords()->getZ() - position) - s->getR();
    }
}

Plane::Type Plane::getType()
{
    return type;
}

double Plane::getPosition()
{
    return position;
}
