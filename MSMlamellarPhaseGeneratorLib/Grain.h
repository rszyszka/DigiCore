#pragma once

class Grain {
private:
	double angle1;
	double angle2;
	double angle3;
	double twinAngleX;
	int twinInside;
	unsigned int childTwins;
public:
	
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

	__declspec(dllexport) void setChildTwins(unsigned int);
	__declspec(dllexport) unsigned int getChildTwins();
};