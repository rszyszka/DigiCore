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
			if (x1 == 0)
				x1 = getLimitX1P(grainIndex);

			if (x2 == this->getSpace()->getXsize() - 1)
				x2 = getLimitX2P(grainIndex) + this->getSpace()->getXsize();

			if (y1 == 0)
				y1 = getLimitY1P(grainIndex);

			if (y2 == this->getSpace()->getYsize() - 1)
				y2 = getLimitY2P(grainIndex) + this->getSpace()->getYsize();

			if (this->getSpace()->is3Dspace() && z1 == 0)
				z1 = getLimitZ1P(grainIndex);

			if (this->getSpace()->is3Dspace() && z2 == this->getSpace()->getZsize() - 1)
				z2 = getLimitZ2P(grainIndex) + this->getSpace()->getZsize();
		}

		Point s1, s2;
		int half = 180;
		alpha = int(alpha + half) % half;
		double at = tan(alpha * pi / 180.0);
		if (alpha == 0 || alpha == 180) {
			s1.setXYZ(x1, int((y1 + y2) / 2.0), z1);
			s2.setXYZ(x2, int((y1 + y2) / 2.0), z1);

			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setY(int(double(y1 + y2)*0.5) + double(y2 - y1)*0.25 + randV);
				s1.setY(int(double(y1 + y2)*0.5) + double(y2 - y1)*0.25 + randV);
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setY(int(double(y1 + y2)*0.5) - double(y2 - y1)*0.25 + randV);
				s1.setY(int(double(y1 + y2)*0.5) - double(y2 - y1)*0.25 + randV);
			}


			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setY(s1.getY() + 1);
				s2.setY(s2.getY() + 1);
				midpointLine(s1, s2, grainIndex);
			}

			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;

			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setY(s1.getY() - d);
					sx2.setY(s2.getY() - d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}

		}
		else if (alpha > 0 && alpha <= 30) {
			s1.setXYZ(x1, int((y1 + y2) / 2.0), z1);

			double x0 = double(s1.getX() - s1.getY() / at);// = double ((s1.getY() - at * s1.getX()) / (-at));
			double b = -at * x0;
			double tempY = at * x2 + b;
			double tempX = (y2 - b) / at;

			if ((x2 - s1.getX())*(x2 - s1.getX()) + (tempY - s1.getY()) * (tempY - s1.getY()) < (tempX - s1.getX())*(tempX - s1.getX()) + (y2 - s1.getY()) * (y2 - s1.getY())) {
				s2.setXYZ(x2, int(tempY), z1);
			}
			else {
				s2.setXYZ(int(tempX), y2, z1);
			}


			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setY(int(s2.getY() + double(y2 - y1)*0.25 + randV));
				s1.setY(int(s1.getY() + double(y2 - y1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setY(int(s2.getY() - double(y2 - y1)*0.25 + randV));
				s1.setY(int(s1.getY() - double(y2 - y1)*0.25 + randV));
			}



			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setY(s1.getY() - 1);
				s2.setY(s2.getY() - 1);
				midpointLine(s1, s2, grainIndex);
			}

			//3d
			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setY(s1.getY() - d);
					sx2.setY(s2.getY() - d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}
		}
		else if (alpha > 30 && alpha < 60) {
			s1.setX(x1);
			s1.setY(y1);
			s1.setZ(z1);
			double x0 = double((s1.getY() - at * s1.getX()) / (-at));
			double b = -at * x0;
			double tempY = at * x2 + b;
			double tempX = (y2 - b) / at;

			if ((x2 - s1.getX())*(x2 - s1.getX()) + (tempY - s1.getY()) * (tempY - s1.getY()) < (tempX - s1.getX())*(tempX - s1.getX()) + (y2 - s1.getY()) * (y2 - s1.getY())) {
				s2.setX(x2);
				s2.setY(int(tempY));
				s2.setZ(z1);
			}
			else {
				s2.setX(int(tempX));
				s2.setY(y2);
				s2.setZ(z1);
			}


			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setX(int(s2.getX() + double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() + double(x2 - x1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setX(int(s2.getX() + double(x2 - x1)*0.5 + randV));
				s1.setX(int(s1.getX() + double(x2 - x1)*0.5 + randV));
			}


			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setX(s1.getX() + 1);
				s2.setX(s2.getX() + 1);
				midpointLine(s1, s2, grainIndex);
			}
			//3d

			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setX(s1.getX() + d);
					sx2.setX(s2.getX() + d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}

		}
		else if (alpha >= 60 && alpha < 90) {
			s1.setX((x1 + x2) / 2);
			s1.setY(y1);
			s1.setZ(z1);
			double x0 = double((s1.getY() - at * s1.getX()) / (-at));
			double b = -at * x0;
			double tempY = at * x2 + b;
			double tempX = (y2 - b) / at;

			if ((x2 - s1.getX())*(x2 - s1.getX()) + (tempY - s1.getY()) * (tempY - s1.getY()) < (tempX - s1.getX())*(tempX - s1.getX()) + (y2 - s1.getY()) * (y2 - s1.getY())) {
				s2.setX(x2);
				s2.setY(int(tempY));
				s2.setZ(z1);
			}
			else {
				s2.setX(int(tempX));
				s2.setY(y2);
				s2.setZ(z1);
			}

			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setX(int(s2.getX() + double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() + double(x2 - x1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setX(int(s2.getX() - double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() - double(x2 - x1)*0.25 + randV));
			}

			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setX(s1.getX() - 1);
				s2.setX(s2.getX() - 1);
				midpointLine(s1, s2, grainIndex);
			}
			//3d
			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setX(s1.getX() - d);
					sx2.setX(s2.getX() - d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}
		}
		else if (alpha == 90) {
			s1.setX(int((x1 + x2)*0.5));
			s1.setY(y1);
			s1.setZ(z1);
			s2.setX(int((x1 + x2)*0.5));
			s2.setY(y2);
			s2.setZ(z1);

			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setX(int(s2.getX() + double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() + double(x2 - x1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setX(int(s2.getX() - double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() - double(x2 - x1)*0.25 + randV));
			}

			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setX(s1.getX() + 1);
				s2.setX(s2.getX() + 1);
				midpointLine(s1, s2, grainIndex);
			}
			//3d
			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setX(s1.getX() + d);
					sx2.setX(s2.getX() + d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}
		}
		else if (alpha > 90 && alpha < 120) {
			s1.setX(int((x1 + x2)*0.5));
			s1.setY(y1);
			s1.setZ(z1);
			double x0 = double((s1.getY() - at * s1.getX()) / (-at));
			double b = -at * x0;
			double tempY = at * x1 + b;
			double tempX = (y2 - b) / at;



			if ((x2 - s1.getX())*(x2 - s1.getX()) + (tempY - s1.getY()) * (tempY - s1.getY()) < (tempX - s1.getX())*(tempX - s1.getX()) + (y2 - s1.getY()) * (y2 - s1.getY())) {
				s2.setX(x1);
				s2.setY(int(tempY));
				s2.setZ(z1);
			}
			else {
				s2.setX(int(tempX));
				s2.setY(y2);
				s2.setZ(z1);
			}

			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setX(int(s2.getX() + double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() + double(x2 - x1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setX(int(s2.getX() - double(x2 - x1)*0.25 + randV));
				s1.setX(int(s1.getX() - double(x2 - x1)*0.25 + randV));
			}

			//2d
			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setX(s1.getX() + 1);
				s2.setX(s2.getX() + 1);
				midpointLine(s1, s2, grainIndex);
			}

			//3d
			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setX(s1.getX() + d);
					sx2.setX(s2.getX() + d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}
		}
		else if (alpha >= 120 && alpha <= 150) {
			s1.setX(x2);
			s1.setY(y1);
			s1.setZ(z1);
			double x0 = double((s1.getY() - at * s1.getX()) / (-at));
			double b = -at * x0;
			double tempY = at * x1 + b;
			double tempX = (y2 - b) / at;

			if ((x2 - s1.getX())*(x2 - s1.getX()) + (tempY - s1.getY()) * (tempY - s1.getY()) < (tempX - s1.getX())*(tempX - s1.getX()) + (y2 - s1.getY()) * (y2 - s1.getY())) {
				s2.setX(x1);
				s2.setY(int(tempY));
				s2.setZ(z1);
			}
			else {
				s2.setX(int(tempX));
				s2.setY(y2);
				s2.setZ(z1);
			}


			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setY(int(s2.getY() + double(y2 - y1)*0.25 + randV));
				s1.setY(int(s1.getY() + double(y2 - y1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setY(int(s2.getY() - double(y2 - y1)*0.25 + randV));
				s1.setY(int(s1.getY() - double(y2 - y1)*0.25 + randV));
			}

			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setY(s1.getY() + 1);
				s2.setY(s2.getY() + 1);
				midpointLine(s1, s2, grainIndex);
			}
			//3d


			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setY(s1.getY() + d);
					sx2.setY(s2.getY() + d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}

			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					s1.setY(s1.getY() + 1);
					s2.setY(s2.getY() + 1);
					s1.setZ(l);
					s2.setZ(l);
					midpointLine(s1, s2, grainIndex);
				}
			}
		}
		else if (alpha >= 150 && alpha < 180) {
			s1.setX(x1);
			s1.setY(int((y1 + y2)*0.5));
			s1.setZ(z1);
			double x0 = double((s1.getY() - at * s1.getX()) / (-at));
			double b = -at * x0;
			double tempY = at * x2 + b;
			double tempX = (y1 - b) / at;
			double d1, d2;
			d1 = sqrt((x2 - s1.getX())*(x2 - s1.getX()) + (tempY - s1.getY()) * (tempY - s1.getY()));
			d2 = sqrt((tempX - s1.getX())*(tempX - s1.getX()) + (y1 - s1.getY()) * (y1 - s1.getY()));
			if (d1 >= d2) {
				s2.setX(int(tempX));
				s2.setY(y1);
				s2.setZ(z1);
			}
			else {
				s2.setX(x2);
				s2.setY(int(tempY));
				s2.setZ(z1);
			}

			int param = 5;
			int randV = rand() % param;
			if (grainsAngles[grainIndex].childTwins == 2) {
				s2.setY(int(s2.getY() + double(y2 - y1)*0.25 + randV));
				s1.setY(int(s1.getY() + double(y2 - y1)*0.25 + randV));
			}
			else if (grainsAngles[grainIndex].childTwins == 3) {
				s2.setY(int(s2.getY() - double(y2 - y1)*0.25 + randV));
				s1.setY(int(s1.getY() - double(y2 - y1)*0.25 + randV));
			}

			for (int d = 0; d <= twinWidth && !this->getSpace()->is3Dspace(); ++d) {
				s1.setY(s1.getY() + 1);
				s2.setY(s2.getY() + 1);
				midpointLine(s1, s2, grainIndex);
			}

			//3d	
			Point sx1, sx2;
			sx1 = s1;
			sx2 = s2;
			for (int l = z1; l <= z2 && this->getSpace()->is3Dspace(); l++) {
				for (int d = 0; d <= twinWidth; ++d) {
					sx1.setY(s1.getY() + d);
					sx2.setY(s2.getY() + d);
					sx1.setZ(l);
					sx2.setZ(l);
					midpointLine(sx1, sx2, grainIndex);
				}
			}
		}
	}
	if(grainIndex < numberOfGrains)
		return false;
	return true;
}

Space * LamellarPhaseGenerator::getSecondPhaseSpace(){ return this->secondPhaseSpace; }

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

int LamellarPhaseGenerator::getLimitX2P(int grainIndex)
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

void LamellarPhaseGenerator::midpointLine(Point k1, Point k2, int nr_ziarna)
{
	int X = this->getSpace()->getXsize();
	int Y = this->getSpace()->getYsize();
	int Z = this->getSpace()->getZsize();

	int k = k1.getZ();
	int x0 = k1.getX();
	int y0 = k1.getY();
	int x1 = k2.getX();
	int y1 = k2.getY();
	int d, dx, dy, ai, bi, xi, yi;
	int x = x0, y = y0;
	if (x0 < x1) {
		xi = 1;
		dx = x1 - x0;
	}
	else {
		xi = -1;
		dx = x0 - x1;
	}

	if (y0 < y1) {
		yi = 1;
		dy = y1 - y0;
	}
	else {
		yi = -1;
		dy = y0 - y1;
	}

	if (nr_ziarna != 0 && this->getSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->getId() == nr_ziarna
		&& this->getSecondPhaseSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->getId() == 0) {
		this->getSecondPhaseSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->setId(int(twinsAngles.size()) - 1);
	}

	if (dx > dy) {
		ai = (dy - dx) * 2;
		bi = dy * 2;
		d = bi - dx;
		while (x != x1) {
			if (d >= 0) {
				x += xi;
				y += yi;
				d += ai;
			}
			else {
				d += bi;
				x += xi;
			}


			//if(x >= X || y >= Y || y < 0 || x < 0)
			//return;

			if (x0 > x1)
				if (x > x0 || x < x1)
					return;

			if (x0 < x1)
				if (x > x1 || x < x0)
					return;

			if (y0 > y1)
				if (y > y0 || y < y1)
					return;

			if (y1 > y0)
				if (y > y1 || y < y0)
					return;

			if (nr_ziarna != 0 && this->getSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->getId() == nr_ziarna
	/*check*/			&& this->getSecondPhaseSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z] == 0) {
	/*tutaj [k]*/			this->getSecondPhaseSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->setId(int(twinsAngles.size()) - 1);
			}
		}
	}
	else {
		ai = (dx - dy) * 2;
		bi = dx * 2;
		d = bi - dy;
		// pêtla po kolejnych y
		while (y != y1) {
			// test wspó³czynnika
			if (d >= 0) {
				x += xi;
				y += yi;
				d += ai;

			}
			else {
				d += bi;
				y += yi;
			}



			if (x0 > x1)
				if (x > x0 || x < x1)
					return;

			if (x0 < x1)
				if (x > x1 || x < x0)
					return;

			if (y0 > y1)
				if (y > y0 || y < y1)
					return;

			if (y1 > y0)
				if (y > y1 || y < y0)
					return;
			//if(x >= X || y >= Y || y < 0 || x < 0)
			//return; 

			if (nr_ziarna != 0 && this->getSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->getId() == nr_ziarna
				&& this->getSecondPhaseSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->getId() == 0) {
				this->getSecondPhaseSpace()->getCells()[(x + X) % X][(y + Y) % Y][(k + Z) % Z]->setId(int(twinsAngles.size()) - 1);
			}
		}
	}
}

