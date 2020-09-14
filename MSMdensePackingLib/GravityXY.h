#pragma once
#include "Gravity.h"

class GravityXY : public Gravity
{
public:
    void applyToSphereVelocity(Sphere* sphere) override {
        sphere->getVelocity()->addToZ(gravityValue);
        sphere->getVelocity()->multiplyZ(GRAVITY_DIR_DRAG);

        sphere->getVelocity()->multiplyX(OTHER_DIR_DRAG);
        sphere->getVelocity()->multiplyY(OTHER_DIR_DRAG);
    }
};

