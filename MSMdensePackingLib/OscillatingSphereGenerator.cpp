#include "OscillatingSphereGenerator.h"

OscillatingSphereGenerator::OscillatingSphereGenerator(int minRadius, int maxRadius, int counter) : LargestSphereGenerator(minRadius, maxRadius), realOriginMaxRadius(originMaxRadius), originCounter(counter)
{
    modifier = 1;
    this->counter = counter;
}

void OscillatingSphereGenerator::resetMaxRadius()
{
    counter--;
    if (counter == 0) {
        changeDirectionIfNecessary();
        originMaxRadius -= modifier;
        counter = originCounter;
    }
   LargestSphereGenerator::resetMaxRadius();
}

void OscillatingSphereGenerator::changeDirectionIfNecessary()
{
    if (modifier > 0 && originMaxRadius == minRadius) {
        modifier *= -1;
    }
    else if (modifier < 0 && originMaxRadius == realOriginMaxRadius) {
        modifier *= -1;
    }
}
