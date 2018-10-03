#pragma once
#include "../MSMcoreLib/Cell.h"
#include "../MSMcoreLib/Point.h"
#include <vector>

using namespace std;

class Grain
{
private:
	vector<Point*> points;
	int id;
public:
	__declspec(dllexport) Grain(vector<Point*>, int);
	__declspec(dllexport) int getId();
	__declspec(dllexport) vector<Point*> getPoints();
};