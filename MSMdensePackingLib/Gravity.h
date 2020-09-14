#pragma once
#include "Sphere.h"

class Gravity
{
public:
    Gravity* changeState();
    void setNext(Gravity* next);
    void reverse();
    virtual void applyToSphereVelocity(Sphere* sphere) = 0;

protected:
     const double GRAVITY_DIR_DRAG = 0.9;
     const double OTHER_DIR_DRAG = 0.99;
     double gravityValue = 0.2;
     Gravity* next;
};

