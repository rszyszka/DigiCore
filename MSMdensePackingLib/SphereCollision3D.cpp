#include "SphereCollision3D.h"
#include <math.h>

void SphereCollision3D::determineAuxiliaryVelocitiesByRotatingForward(Sphere* sphere, Sphere* otherSphere)
{
    angle1 = computeXYAngle(sphere->getCoords(), otherSphere->getCoords());
    u1 = rotateByXY(sphere->getVelocity(), angle1);
    angle2 = computeXZAngle(sphere->getCoords(), &u1);
    u1 = rotateByXZ(&u1, angle2);
    u2 = rotateByXZ(&rotateByXY(otherSphere->getVelocity(), angle1), angle2);
}

Velocity SphereCollision3D::determineFinalVelocityByRotatingBackward(Velocity* v)
{
    return rotateByXY(&rotateByXZ(v, -angle2), -angle1);
}

double SphereCollision3D::computeMass(Sphere* sphere)
{
    return 1.3333333333333333333 * PI * pow(sphere->getR(), 3);
}
