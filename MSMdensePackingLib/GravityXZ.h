#pragma once
#include "Gravity.h"
class GravityXZ : public Gravity
{
public:
    void applyToSphereVelocity(Sphere* sphere) override {
        sphere->getVelocity()->addToY(gravityValue);
        sphere->getVelocity()->multiplyY(GRAVITY_DIR_DRAG);

        sphere->getVelocity()->multiplyX(OTHER_DIR_DRAG);
        sphere->getVelocity()->multiplyZ(OTHER_DIR_DRAG);
    }
};

