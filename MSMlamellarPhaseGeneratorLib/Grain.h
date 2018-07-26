#pragma once

class Grain {
private:

	const double pi = acos(-1.0);

	double angle1;
	double angle2;
	double angle3;
	double twinAngleX;
	int twinInside;

public:
	
	unsigned int childTwins;

	__declspec(dllexport) Grain();
	__declspec(dllexport) ~Grain();
	__declspec(dllexport) void setAngle1(double);
	__declspec(dllexport) void setAngle2(double);
	__declspec(dllexport) void setAngle3(double);

	__declspec(dllexport) double getAngle1();
	__declspec(dllexport) double getAngle2();
	__declspec(dllexport) double getAngle3();

	__declspec(dllexport) void setTwinAngleX(double);
	__declspec(dllexport) double getTwinAngleX();

	__declspec(dllexport) void setTwinInside(int);
	__declspec(dllexport) int getTwinInside();
};