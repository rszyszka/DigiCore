#pragma once
#include "Sphere.h"

class Plane : public BinObject
{
public:
	enum class Type {
		YZ,XZ,XY
	};

	__declspec(dllexport) Plane(Type type, double position);
	__declspec(dllexport) double computeDistance(Sphere* s);
	__declspec(dllexport) Type getType();
	__declspec(dllexport) double getPosition();

private:
	const Type type;
	const double position;
};

