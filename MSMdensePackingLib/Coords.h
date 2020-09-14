#pragma once
#include<iostream>
class Coords
{
public:
	Coords(double, double, double);
	static Coords* coords(double, double);
	static Coords* coords(double, double, double);
	double getX();
	double getY();
	double getZ();
	void setX(double);
	void setY(double);
	void setZ(double);
	bool operator==(const Coords o) const;

private:
	double x, y, z;
};
