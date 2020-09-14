#pragma once
#include "Coords.h"
#include "Velocity.h"
#include "BinObject.h"
#include <iostream>

class Sphere : public BinObject
{
public:
	Sphere(int);
	~Sphere() { delete coords, velocity; };
	int getR();
	Coords* getCoords();
	void setCoords(Coords);
	Velocity* getVelocity();
	void setVelocity(Velocity velocity);

protected:
	const int r;
	Coords* coords;

private:
	Velocity* velocity;
};

