#pragma once
#include "Sphere.h"

class SphereCollision
{
public:
    const double PI = 3.14159265358979323846;

    SphereCollision();
    void resolve(Sphere* sphere, Sphere* otherSphere);

protected:
     Velocity u1;
     Velocity u2;
     Velocity v1;
     Velocity v2;

     virtual void determineAuxiliaryVelocitiesByRotatingForward(Sphere* sphere, Sphere* otherSphere) = 0;
     void computeNewVelocitiesUsingOneDimNewtonian(Sphere* sphere, Sphere* otherSphere);
     virtual Velocity determineFinalVelocityByRotatingBackward(Velocity* v) = 0;
     double computeXYAngle(Coords* coords, Coords* otherCoords);
     Velocity rotateByXY(Velocity* velocity, double angle);
     double computeXZAngle(Coords* coords, Coords* otherCoords);
     Velocity rotateByXZ(Velocity* velocity, double angle);
     virtual double computeMass(Sphere* sphere) = 0;
};

