#pragma once
#include "../MSMcoreLib/Point.h"
#include "Direction.h"

class Ball : public Point
{
private:
	int radius;
	Direction dirX;
	Direction dirY;
	Direction dirZ;
	bool side;
public:
	__declspec(dllexport) Ball();
	__declspec(dllexport) Ball(int x, int y, int z);
	__declspec(dllexport) Ball(int x, int y, bool side);

	__declspec(dllexport) Ball(int x, int y, bool side, int radius, Direction dirX, Direction dirY);

	__declspec(dllexport) Direction getDirX() const;
	__declspec(dllexport) Direction getDirY() const;
	__declspec(dllexport) Direction getDirZ() const;
	__declspec(dllexport) int getRadius() const;
	__declspec(dllexport) void setRadius(int radius);
	__declspec(dllexport) bool isSide();
	__declspec(dllexport) void setDirX(Direction dirX);
	__declspec(dllexport) void setDirY(Direction dirY);
	__declspec(dllexport) void setDirZ(Direction dirZ);
	__declspec(dllexport) void setDirXYZ(Direction dirX, Direction dirY, Direction dirZ);
	__declspec(dllexport) void setDirXY(Direction dirX, Direction dirY);
	__declspec(dllexport) void setSide(bool side);

	__declspec(dllexport) bool operator==(const Ball*p) const
	{
		return this->getX() == p->getX() && this->getY() == p->getY()
			&& this->getDirX() == p->getDirX() && this->getDirY() == p->getDirY()
			&& this->getRadius() == p->getRadius();
	}
};