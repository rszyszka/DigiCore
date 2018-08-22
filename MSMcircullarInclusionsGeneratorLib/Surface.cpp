#include "Surface.h"

Surface::Surface(int radius, int xSize, int ySize) : PI(acos(-1.0))
{
	this->xSize = xSize;
	this->ySize = ySize;
	maxRadius = radius;
	maxArea = (int)(PI*pow(radius, 2));
}

int Surface::countMaxArea(int x, int y)
{
	int area = 0;
	if (x - maxRadius > 0 && x + maxRadius < xSize && y - maxRadius > 0 && y + maxRadius < ySize)
	{
		area = maxArea;
	}
	else
	{
		area = countNotRoundArea(x, y, maxRadius);
	}
	return area;
}

int Surface::countArea(int x, int y, int radius)
{
	int area = 0;
	if (x - radius > 0 && x + radius < xSize && y - radius > 0 && y + radius < ySize)
	{
		area = (int)(PI * pow(radius, 2));
	}
	else
	{
		area = countNotRoundArea(x, y, radius);
	}
	return area;
}

int Surface::countNotRoundArea(int x, int y, int radius)
{
	int area = 0;
	if ((x - radius > 0 && x + radius < xSize) && !(y - radius > 0 && y + radius < ySize) ||
		!((x - radius > 0 && x + radius < xSize) && (y - radius > 0 && y + radius < ySize)))
	{
		area = areaLimitedByOneBorder(x, y, radius);
	}
	else
	{
		area = areaLimitedByTwoBorders(x, y, radius);
	}
	return area;
}

int Surface::areaLimitedByOneBorder(int x, int y, int radius)
{
	int area;
	int angle = 0;
	int areaofCircle = (int)round(PI * pow(radius, 2));
	if (x + radius>xSize)
	{
		angle = (int)round(((cos((xSize - x) / (double)radius)) * 360 / PI));
	}
	else if (x - radius<0)
	{
		angle = (int)round((cos(x / (double)radius) * 360 / PI));
	}
	if (y + radius>ySize)
	{
		angle = (int)round((cos((xSize - y) / (double)radius) * 360 / PI));
	}
	else if (y - radius<0)
	{
		angle = (int)round((cos(y / (double)radius) * 360 / PI));
	}

	area = (int)round((angle / (double)360 * PI*pow(radius, 2)) - (pow(radius, 2)*cos(angle)*0.5));
	return areaofCircle - area;
}

int Surface::areaLimitedByTwoBorders(int x, int y, int radius)
{
	int surface = 0;
	int lengthx = x + radius >= xSize ? xSize : x + radius;
	int lengthy = y + radius >= ySize ? ySize : y + radius;
	int startx = x - radius > 0 ? 0 : x - radius;
	int starty = y - radius > 0 ? 0 : y - radius;
	for (int i = startx; i < lengthx; i++)
	{
		for (int j = starty; j < lengthy; j++)
		{
			surface = sqrt(pow(x - i, 2) + pow(y - j, 2)) <= radius ? surface++ : surface;
		}
	}
	return surface;
}