#pragma once

class Point
{
private:
	int x, y, z;

public:
	__declspec(dllexport) Point();
	__declspec(dllexport) Point(int x, int y, int z);
	__declspec(dllexport) Point(int x, int y);

	__declspec(dllexport) int getX() const;
	__declspec(dllexport) int getY() const;
	__declspec(dllexport) int getZ() const;
	__declspec(dllexport) void setX(int x);
	__declspec(dllexport) void setY(int y);
	__declspec(dllexport) void setZ(int z);
	__declspec(dllexport) void setXYZ(int x, int y, int z);
	__declspec(dllexport) void setXY(int x, int y);

	__declspec(dllexport) bool operator==(const Point*p) const
	{
		return x == p->x && y == p->y;
	}
};