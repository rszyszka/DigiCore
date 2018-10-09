#include "BallSchema2D.h"

BallSchema2D::~BallSchema2D()
{
	for (int i = 0; i < size; i++)
	{
		delete[] schema[i];
	}
	delete[] schema;
}

BallSchema2D::BallSchema2D(int radius) : size(radius*2)
{
	schema = new bool*[size];
	for (int i = 0; i < size; i++)
	{
		schema[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			schema[i][j] = false;
		}
	}
}

const int BallSchema2D::getSize()
{
	return size;
}

bool ** BallSchema2D::getSchema()
{
	return schema;
}