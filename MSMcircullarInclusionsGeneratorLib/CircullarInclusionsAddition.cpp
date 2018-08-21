#include "CircullarInclusionsAddition.h"

CircullarInclusionsAddition::CircullarInclusionsAddition(Space * space) : Simulation(space)
{
	srand(time(nullptr));

	xSize = space->getXsize();
	ySize = space->getYsize();
	zSize = space->getZsize();

	radius = 6;
	desiredSurface = (int)(10 * xSize * ySize / (double)100);
	desiredVolume = 10;

	inclusionsSpace = new Space(space->getXsize(), space->getYsize(), space->getZsize(), space->getNeighborhood());
	progress = 100 / (xSize * ySize * zSize);
}

bool CircullarInclusionsAddition::performStep()
{
	//TODO::
	if (!this->inclusionsSpace->is3Dspace()) {
		
	}
	return false;
}

void CircullarInclusionsAddition::setUnmixedGrid2D()
{
	int radiusfee = radius + 3;
	int xCoord, yCoord;
	bool isOdd, side;
	int lengthChecker = 0;
	int CirclesInXDirs = (int)(round((xSize - radiusfee) / (double)(radiusfee * 2))) + 1;
	int CirclesInXDir = (int)round(xSize / (double)(radiusfee * 2)) + 1;
	int heightInYDir = (int)(ceil(sqrt((pow(radiusfee * 2, 2) - pow(radiusfee, 2)))));
	int CirclesInYDir = ySize / (heightInYDir)+1;
	for (int i = 0; i < CirclesInYDir; i++)
	{
		lengthChecker = i % 2 == 0 ? CirclesInXDir : CirclesInXDirs;
		isOdd = i % 2 != 0 ? true : false; //bylo == zamiast != -- blad nazewniczy??
		for (int j = 0; j < lengthChecker; j++)
		{
			yCoord = i * heightInYDir;
			xCoord = isOdd ? j * 2 * radiusfee : j * 2 * (radiusfee)+radiusfee + 1;
			if (xCoord > xSize + radiusfee || xCoord < 0 - radiusfee)
			{
				xCoord = xSize - 1 + radiusfee;
			}
			if (yCoord > ySize + radiusfee || yCoord < 0 - radiusfee)
			{
				ySize = ySize - 1 + radiusfee;
			}
			side = rand() % 2 == 1 ? true : false;
			Ball ball(xCoord, yCoord, side);
			balls.push_back(ball);
		}
	}
}

void CircullarInclusionsAddition::addMinimumAmountOfCircles()
{
	double actualSurface = 0;
	double pattern = (acos(-1.0) * pow(radius, 2));
	while (desiredSurface > actualSurface)
	{
		if (balls.size() == 0)
			break;
		Ball ball = balls[rand() % balls.size()];
		ball.setRadius(rand() % (radius - 5) + 6); //= rand.Next(6, Radius + 1);
		//TODO:: actualSurface = 
	}
}

int CircullarInclusionsAddition::getProgress()
{
	return progress;
}

Space * CircullarInclusionsAddition::getInclusionsSpace()
{
	return inclusionsSpace;
}

vector<Ball> CircullarInclusionsAddition::getActiveBalls()
{
	return activeBalls;
}

vector<Ball> CircullarInclusionsAddition::getBalls()
{
	return balls;
}
