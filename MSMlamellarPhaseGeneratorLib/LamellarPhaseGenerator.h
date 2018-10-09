#pragma once
#include "../MSMcoreLib/Simulation.h"
#include "../MSMcoreLib/Point.h"
#include <math.h>
#include "StructureAngles.h"

class LamellarPhaseGenerator : public Simulation
{
private:

	int progress;
	int numberOfGrains;

	const double pi = acos(-1.0);

	vector<StructureAngles> grainsAngles;
	vector<StructureAngles> twinsAngles;

	int grainIndex = 1;
	int twinWidth;

	void KQ4_eul(double r[5], double ang[4]);
	void Keul_Q4(double euler[4], double q[5]);
	double Karc(double, double);
	void KQ4mult(int, double*, double*);
	void KQ4_mat(double q[5], double mat[4][4]);

	void defineStructureAngles();
	void midpointLine(Point, Point, int);

	int getLimitX1(int);
	int getLimitX2(int);
	int getLimitY1(int);
	int getLimitY2(int);
	int getLimitZ1(int);
	int getLimitZ2(int);
	int getLimitX1P(int);
	int getLimitX2P(int);
	int getLimitY1P(int);
	int getLimitY2P(int);
	int getLimitZ1P(int);
	int getLimitZ2P(int);
	
public:
	__declspec(dllexport) LamellarPhaseGenerator(Space *space, int twinWidth);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) int getProgress() override;
	__declspec(dllexport) vector<StructureAngles> getGrainsAngles();
	__declspec(dllexport) vector<StructureAngles> getTwinsAngles();
	__declspec(dllexport) void computeAngles(double, int, int);
};