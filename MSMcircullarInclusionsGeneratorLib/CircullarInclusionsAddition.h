#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "Ball.h"
#include "Surface.h"
#include "BallSchema2D.h"
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
	void setUnmixedGrid3D();
	void addMinimumAmountOfCircles();
	void setBalls3D();
	void adjustSurface();
	void mixBalls2D();
	void mixBalls3D();
	void reduceBalls3D();
	bool checkIfInRange(Ball movedBall, Direction dir);
	bool checkIfInRange(Ball movedBall);
	void fill2dSpace();
	void fill3dSpace();
	BallSchema2D* create2DSchema(int radius);
	void fill2dBall(BallSchema2D*, int x, int y, int radius);
	void ballDirectionInitializer(Ball &ball);
	void directionSetter(Ball &ball, Ball &notMovedBall);
	void moveBall(Ball &ball);
public:
	__declspec(dllexport) CircullarInclusionsAddition(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
	__declspec(dllexport) Space* getInclusionsSpace();
	__declspec(dllexport) vector<Ball> getActiveBalls();
	__declspec(dllexport) vector<Ball> getBalls();
};