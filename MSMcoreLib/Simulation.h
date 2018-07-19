#pragma once
#include "Space.h"

class Simulation
{
protected:
	Space *space;
	unsigned int xSize, ySize, zSize;

private:
	bool notFinished;
	bool stepByStep;
	void nextStep();

public:
	__declspec(dllexport) virtual ~Simulation();
	__declspec(dllexport) virtual bool performStep() = 0;
	__declspec(dllexport) virtual int getProgress() = 0;

	__declspec(dllexport) Simulation(Space *space);
	__declspec(dllexport) void simulateWithOneThread();
	__declspec(dllexport) void simulateContinuously();

	__declspec(dllexport) Space* getSpace() const;
	__declspec(dllexport) void setSpace(Space *space);
	__declspec(dllexport) bool isFinished() const;
};
