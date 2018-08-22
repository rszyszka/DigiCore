#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "Ball.h"
#include "Surface.h"
#include <math.h>
#include <time.h>

class CircullarInclusionsAddition : public Simulation
{
private:
	int progress;
	Space* inclusionsSpace;
	int xSize;
	int ySize;
	int zSize;
	int radius, desiredSurface, desiredVolume;
	vector<Ball> activeBalls;
	vector<Ball> balls;
	Surface* surface;

	void setUnmixedGrid2D();
	void addMinimumAmountOfCircles();
	void adjustSurface();
	void mixBalls2D();
	bool checkIfInRange(Ball movedBall, Direction dir);
	void fill2DTable();
	bool** create2DSchema(int radius);

public:
	__declspec(dllexport) CircullarInclusionsAddition(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
	__declspec(dllexport) Space* getInclusionsSpace();
	__declspec(dllexport) vector<Ball> getActiveBalls();
	__declspec(dllexport) vector<Ball> getBalls();
};