#include "RandomSphereGenerator.h"
#include <stdlib.h>
#include <time.h> 

RandomSphereGenerator::RandomSphereGenerator(int minRadius, int maxRadius) : AbstractSphereGenerator(minRadius, maxRadius)
{
}

Sphere* RandomSphereGenerator::generateNewSphere()
{
    int diff = maxRadius - minRadius + 1;
    int radius = diff == 0 ? minRadius : (rand() % diff) + minRadius;
    return new Sphere(radius);
}
