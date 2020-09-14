#pragma once
#include "Gravity.h"
class GravityYZ : public Gravity
{
public:
    void applyToSphereVelocity(Sphere* sphere) override {
        sphere->getVelocity()->addToX(gravityValue);
        sphere->getVelocity()->multiplyX(GRAVITY_DIR_DRAG);

        sphere->getVelocity()->multiplyY(OTHER_DIR_DRAG);
        sphere->getVelocity()->multiplyZ(OTHER_DIR_DRAG);
    }
};

