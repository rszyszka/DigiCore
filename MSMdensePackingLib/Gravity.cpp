#include "Gravity.h"

Gravity* Gravity::changeState()
{
    if (gravityValue < 0) {
        reverse();
        return next;
    }
    reverse();
    return this;
}

void Gravity::setNext(Gravity* next)
{
    this->next = next;
}

void Gravity::reverse()
{
    gravityValue = -gravityValue;
}
