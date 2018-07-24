#pragma once
#include "../MSMcoreLib/Simulation.h"
#include <math.h>
#include "Grain.h"

class LamellarPhaseGenerator : public Simulation
{
private:
	Space *secondPhaseSpace;
	int numberOfGrains;

	const double pi = acos(-1.0);

	vector<Grain> grainsAngles;
	vector<Grain> twinsAngles;

	void KQ4_eul(double r[5], double ang[4]);
	void Keul_Q4(double euler[4], double q[5]);
	double Karc(double, double);
	void KQ4mult(int, double*, double*);
	void KQ4_mat(double q[5], double mat[4][4]);
	
public:
	__declspec(dllexport) LamellarPhaseGenerator(Space *space);
	__declspec(dllexport) bool performStep() override;
	__declspec(dllexport) vector<Grain> getGrainsAngles();
	__declspec(dllexport) vector<Grain> getTwinsAngles();
	__declspec(dllexport) void computeAngles(double, int, int);
};
