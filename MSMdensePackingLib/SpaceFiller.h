#pragma once
#include "../MSMcoreLib/Space.h"
#include "Bin.h"
class SpaceFiller
{
public:
    __declspec(dllexport) SpaceFiller(Space* space);
    __declspec(dllexport) void fillWithAllSpheres(Bin* bin);
    void fillWithSphere(Sphere* sphere, int id);
    int getNumberOfFilledCells();

private:
    Space* space;
    int numberOfFilledCells;
    bool isInCircle(int x, int y, int z, Sphere* sphere);
};

