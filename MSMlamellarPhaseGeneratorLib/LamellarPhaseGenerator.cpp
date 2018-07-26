#include "LamellarPhaseGenerator.h"
#include <ctime>

LamellarPhaseGenerator::LamellarPhaseGenerator(Space * space) : Simulation(space)
{
	srand(time(nullptr));
	numberOfGrains = this->space->getMaxId();
	secondPhaseSpace = new Space();
	
	Grain a;
	grainsAngles.push_back(a); //id == 0;
	twinsAngles.push_back(a); //id == 0;
	for (int i = 1; i <= numberOfGrains; i++)
	{
		grainsAngles.push_back(a);
	}
}

bool LamellarPhaseGenerator::performStep()
{
	double alpha = (rand() % 180) * pi / 180.0;
	
	Grain a;
	while (grainsAngles[grainIndex].childTwins < 3) {
		twinsAngles.push_back(a);
		grainsAngles[grainIndex].childTwins++;

		if (grainsAngles[grainIndex].childTwins == 1) {
			grainsAngles[grainIndex].setTwinAngleX(alpha);
			grainsAngles[grainIndex].setTwinInside(twinsAngles.size() - 1);
			computeAngles(alpha, grainIndex, twinsAngles.size() - 1);//compute angles
		}
		else {
			int tID, tNewID;
			tNewID = twinsAngles.size() - 1;
			tID = grainsAngles[grainIndex].getTwinInside();
			double ang;

			ang = this->twinsAngles[tID].getAngle1();
			this->twinsAngles[tNewID].setAngle1(ang);

			ang = this->twinsAngles[tID].getAngle2();
			this->twinsAngles[tNewID].setAngle2(ang);

			ang = this->twinsAngles[tID].getAngle3();
			this->twinsAngles[tNewID].setAngle3(ang);
		}

		int x1, x2, y1, y2, z1, z2;

		x1 = getLimitX1(grainIndex);
		x2 = getLimitX2(grainIndex);
		y1 = getLimitY1(grainIndex);
		y2 = getLimitY2(grainIndex);
		z1 = getLimitZ1(grainIndex);
		z2 = getLimitZ2(grainIndex);

		if (this->getSpace()->getBoundaryConditions() == BoundaryConditions(Periodic)) {
			//TODO
		}

	}
	return false;
}

vector<Grain> LamellarPhaseGenerator::getGrainsAngles() { return this->grainsAngles; }
vector<Grain> LamellarPhaseGenerator::getTwinsAngles() { return this->twinsAngles; }

void LamellarPhaseGenerator::computeAngles(double alpha, int grainId, int twinId)
{
	double c_over_a, Nhex[4 + 1], Bhex[4 + 1], N[3 + 1], B[3 + 1], v[3 + 1], norm,
		q1[4 + 1], q2[4 + 1], phi[3 + 1], fpi, beta, sq3;
	double R[3 + 1][3 + 1] = { 0.0 };
	int i, j;
	//k;

	sq3 = sqrt(3.0);
	fpi = pi / 180.0;
	// define c over a ratio
	c_over_a = 1.587;
	//selected one twin system

	Nhex[1] = 0.0;
	Nhex[2] = -1.0;
	Nhex[3] = 1.0;
	Nhex[4] = 2.0;
	Bhex[1] = 0.0;
	Bhex[2] = 1.0;
	Bhex[3] = -1.0;
	Bhex[4] = 1.0;
	// 'express N & B in cubic reference frame'
	N[1] = Nhex[1];
	N[2] = (Nhex[2] - Nhex[3]) / sq3;
	N[3] = Nhex[4] / c_over_a;
	norm = sqrt(N[1] * N[1] + N[2] * N[2] + N[3] * N[3]);
	for (i = 1; i <= 3; i++)
		N[i] = N[i] / norm;

	B[1] = Bhex[1];
	B[2] = (Bhex[2] - Bhex[3]) / sq3;
	B[3] = Bhex[4] * c_over_a / 1.5;
	norm = sqrt(B[1] * B[1] + B[2] * B[2] + B[3] * B[3]);

	for (i = 1; i <= 3; i++)
		B[i] = B[i] / norm;

	//'(From now on, twin plane normal is expected to be in the x2 x3 plane)'
	// 'Compute angle of twin plane relative to x2'
	if (abs(B[2]) > 1.0e-10)
		beta = atan(B[3] / B[2]) / fpi;
	else if (B[3]>0.0)
		beta = 90.0;
	else
		beta = -90.0;

	// 'Euler angles bringing the twin plane at an angle alpha'
	// 'relative to x1 in the x1 x2 macroscopic reference frame'

	phi[1] = alpha - beta;
	phi[2] = -90.0;
	phi[3] = -90.0;

	if (this->getSpace()->is3Dspace()) {
		phi[2] = -double(rand() % 90);
		phi[3] = -double(rand() % 90);
	}

	this->grainsAngles[grainId].setAngle1(phi[1]);
	this->grainsAngles[grainId].setAngle2(phi[2]);
	this->grainsAngles[grainId].setAngle3(phi[3]);

	// 'corresponding quaternion & rotation matrix'
	Keul_Q4(phi, q1);

	//*********************************
	KQ4_mat(q1, R);

	for (i = 1; i <= 3; i++) {
		v[i] = 0.0;
		for (j = 1; j <= 3; j++)
			v[i] = v[i] + R[j][i] * N[j];
	}

	for (i = 1; i <= 3; i++) {
		v[i] = 0.0;
		for (j = 0; j <= 3; j++) {
			v[i] = v[i] + R[j][i] * B[j];
		}
	}

	q2[1] = 0.0;
	q2[2] = N[1];
	q2[3] = N[2];
	q2[4] = N[3];

	KQ4mult(1, q2, q1);

	KQ4_eul(q2, phi);

	this->twinsAngles[twinId].setAngle1(phi[1]);
	this->twinsAngles[twinId].setAngle2(phi[2]);
	this->twinsAngles[twinId].setAngle3(phi[3]);
}

int LamellarPhaseGenerator::getLimitX1(int grainIndex)
{
	for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
		for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return i;
				}
			}
		}
	}
	return -1;
}

int LamellarPhaseGenerator::getLimitX2(int grainIndex)
{
	for (int i = this->getSpace()->getXsize() - 1; i >= 0; --i) {
		for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return i;
				}
			}
		}
	}
	return -1;
}

int LamellarPhaseGenerator::getLimitY1(int grainIndex)
{
	for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return j;
				}
			}
		}
	}
	return -1;
}

int LamellarPhaseGenerator::getLimitY2(int grainIndex)
{
	for (int j = this->getSpace()->getYsize() - 1; j >= 0; --j) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return j;
				}
			}
		}
	}
	return -1;
}

int LamellarPhaseGenerator::getLimitZ1(int grainIndex)
{
	for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return k;
				}
			}
		}
	}
	return -1;
}

int LamellarPhaseGenerator::getLimitZ2(int grainIndex)
{
	for (int k = this->getSpace()->getZsize() - 1; k >= 0; --k) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return k;
				}
			}
		}
	}
	return -1;
}

int LamellarPhaseGenerator::getLimitX1P(int grainIndex)
{
	for (int i = this->getSpace()->getXsize() / 2; i < this->getSpace()->getXsize(); ++i) {
		for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return i;
				}
			}
		}
	}

	return getLimitX1(grainIndex);
}

int LamellarPhaseGenerator::getLimitX1P(int grainIndex)
{
	for (int i = this->getSpace()->getXsize() / 2; i >= 0; --i) {
		for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return i;
				}
			}
		}
	}

	return getLimitX2(grainIndex);
}

int LamellarPhaseGenerator::getLimitY1P(int grainIndex)
{
	for (int j = this->getSpace()->getYsize() / 2; j < this->getSpace()->getYsize(); ++j) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return j;
				}
			}
		}
	}

	return getLimitY1(grainIndex);
}

int LamellarPhaseGenerator::getLimitY2P(int grainIndex)
{
	for (int j = this->getSpace()->getYsize() / 2; j >= 0; --j) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int k = 0; k < this->getSpace()->getZsize(); ++k) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return j;
				}
			}
		}
	}

	return getLimitY2(grainIndex);
}

int LamellarPhaseGenerator::getLimitZ1P(int grainIndex)
{
	for (int k = this->getSpace()->getZsize() / 2; k < this->getSpace()->getZsize(); ++k) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return k;
				}
			}
		}
	}

	return getLimitZ1(grainIndex);
}

int LamellarPhaseGenerator::getLimitZ2P(int grainIndex)
{
	for (int k = this->getSpace()->getZsize() / 2; k >= 0; --k) {
		for (int i = 0; i < this->getSpace()->getXsize(); ++i) {
			for (int j = 0; j < this->getSpace()->getYsize(); ++j) {
				if (this->getSpace()->getCells()[i][j][k]->getId() == grainIndex) {
					return k;
				}
			}
		}
	}

	return getLimitZ1(grainIndex);
}

void LamellarPhaseGenerator::KQ4_eul(double r[5], double ang[4]) {

	double fpi = pi / 180.0;

	int i;
	double tmp, msin, mcos;
	if (r[1] < 0.0) {
		for (i = 1; i <= 4; i++) {
			r[i] = -r[i];
		}
	}

	tmp = r[1] * r[1] + r[4] * r[4];

	if (abs(1.0 - tmp)<1.0e-7) {
		mcos = r[1];
		msin = r[4];
		ang[1] = 2.0 * Karc(msin, mcos) - pi / 4.0;
		ang[2] = 0.0;
		ang[3] = pi / 4.0;
	}
	else if (abs(tmp) < 1.0e-7) {
		mcos = r[2];
		msin = r[3];
		ang[1] = 2.0*Karc(msin, mcos) + pi / 4.0;
		ang[2] = pi;
		ang[3] = pi / 4.0;
	}
	else {
		ang[2] = acos(2.0*tmp - 1.0);
		msin = r[2] * r[4] + r[1] * r[3];
		mcos = -r[3] * r[4] + r[1] * r[2];
		ang[1] = Karc(msin, mcos);
		msin = r[2] * r[4] - r[1] * r[3];
		mcos = r[3] * r[4] + r[1] * r[2];
		ang[3] = Karc(msin, mcos);
	}
}

void LamellarPhaseGenerator::Keul_Q4(double euler[4], double q[5])
{
	double fpi = pi / 180.0;
}

double LamellarPhaseGenerator::Karc(double si, double co) {

	double fpi = pi / 180.0;
	double tmp;

	if (abs(co) <= 1.0e-10) {
		if (si > 0.0) {
			tmp = pi / 2.0;
		}
		if (si < 0.0) {
			tmp = -pi / 2.0;
		}
	}
	else {
		if (co > 0.0) {
			tmp = atan(si / co);
		}
		if (co < 0.0) {
			tmp = atan(si / co) + pi;
		}
	}

	if (tmp > pi)
		tmp = tmp - 2.0 * pi;

	return tmp;
}

void LamellarPhaseGenerator::KQ4mult(int Res, double* q_1, double* q_2) {

	int i;
	double q_tmp[5];

	q_tmp[1] = q_1[1] * q_2[1];

	for (i = 2; i <= 4; i++) {
		q_tmp[1] = q_tmp[1] - q_1[i] * q_2[i];
		q_tmp[i] = q_1[1] * q_2[i] + q_2[1] * q_1[i];
	}

	q_tmp[2] = q_tmp[2] - (q_1[3] * q_2[4] - q_1[4] * q_2[3]);
	q_tmp[3] = q_tmp[3] - (q_1[4] * q_2[2] - q_1[2] * q_2[4]);
	q_tmp[4] = q_tmp[4] - (q_1[2] * q_2[3] - q_1[3] * q_2[2]);

	if (Res == 1) {
		for (i = 1; i <= 4; i++) {
			q_1[i] = q_tmp[i];
		}
	}
	else {
		for (i = 1; i <= 4; i++) {
			q_2[i] = q_tmp[i];
		}
	}


}
void LamellarPhaseGenerator::KQ4_mat(double q[5], double mat[4][4]) {

	double tmp1, tmp2;
	int i, j;
	tmp1 = q[1] * q[1] - 0.5;

	for (i = 1; i <= 3; i++) {
		mat[i][i] = q[i + 1] * q[i + 1] + tmp1;
	}

	tmp1 = q[2] * q[3];
	tmp2 = q[1] * q[4];
	mat[2][1] = tmp1 - tmp2;
	mat[1][2] = tmp1 + tmp2;
	tmp1 = q[2] * q[4];
	tmp2 = q[1] * q[3];
	mat[3][1] = tmp1 + tmp2;
	mat[1][3] = tmp1 - tmp2;
	tmp1 = q[3] * q[4];
	tmp2 = q[1] * q[2];
	mat[3][2] = tmp1 - tmp2;
	mat[2][3] = tmp1 + tmp2;

	for (i = 1; i <= 3; i++) {
		for (j = 1; j <= 3; j++)
			mat[i][j] *= 2.0;
	}
}

