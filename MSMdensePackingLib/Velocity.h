#pragma once
#include "Coords.h"
class Velocity : public Coords
{
public:
	__declspec(dllexport) Velocity(double x, double y);
	__declspec(dllexport) Velocity(double x, double y, double z);
	__declspec(dllexport) void negateX();
	__declspec(dllexport) void negateY();
	__declspec(dllexport) void negateZ();
	__declspec(dllexport) void addToX(double value);
	__declspec(dllexport) void addToY(double value);
	__declspec(dllexport) void addToZ(double value);
	__declspec(dllexport) void multiplyX(double value);
	__declspec(dllexport) void multiplyY(double value);
	__declspec(dllexport) void multiplyZ(double value);
};
