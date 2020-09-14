#include "ForEachMinDistance.h"
#include "Utils.h"

ForEachMinDistance::ForEachMinDistance(Bin* bin)
{
	this->bin = bin;
}

double ForEachMinDistance::compute(Hole* hole)
{
    double minDistance = determineMinDistanceToPlanes(hole);
    for (Sphere* sphere : bin->getSpheres()) {
        if (isBinObjectOneOfHolesParents(sphere, hole)) {
            continue;
        }
        double currentDistance = computeDistanceBetweenCircuits(sphere, hole);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
        }
    }
    return minDistance;
}

double ForEachMinDistance::determineMinDistanceToPlanes(Hole* hole)
{
    double minDistance = LONG_MAX;
    for (Plane* plane : bin->getPlanes()) {
        if (isBinObjectOneOfHolesParents(plane, hole)) {
            continue;
        }
        double currentDistance = plane->computeDistance(hole);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
        }
    }
    return minDistance;
}
