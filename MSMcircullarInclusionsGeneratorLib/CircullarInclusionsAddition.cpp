#include "CircullarInclusionsAddition.h"
#include <iostream>
#include "Volume.h"

CircullarInclusionsAddition::CircullarInclusionsAddition(Space * space, int radius, int desiredVolume) : Simulation(space)
{
	srand(time(nullptr));

	this->radius = radius;
	desiredSurface = desiredVolume == 0 ? desiredVolume : xSize * ySize * desiredVolume * 0.01;
	//desiredSurface = (int)(10 * xSize * ySize / (double)100);
	this->desiredVolume = desiredVolume;

	this->surface = new Surface(radius, xSize, ySize);

	progress = 100 / (xSize * ySize * zSize);
}

bool CircullarInclusionsAddition::performStep()
{

	if (this->space->is3Dspace()) {

		cout << "3D SIMULATION" << endl;
		cout << "step1 - setUnmixedGrid..." << endl;
		setUnmixedGrid3D();
		cout << "step2 - setBalls..." << endl;
		setBalls3D();
		cout << "step3 - mixBalls..." << endl;
		mixBalls3D();
		//cout << "step4 - reduceBalls ..." << endl;
		//reduceBalls3D();
		cout << "step5 - fillSpace..." << endl;
		fill3dSpace();
		cout << "DONE!" << endl;
	}
	else {

		cout << "2D SIMULATION" << endl;
		cout << "step1 - setUnmixedGrid..." << endl;
		setUnmixedGrid2D();
		cout << "step2 - addMinimumAmountOfCircles..." << endl;
		addMinimumAmountOfCircles();
		cout << "step3 - adjustSurface ..." << endl;
		adjustSurface();
		cout << "step4 - mixBalls..." << endl;
		mixBalls2D();
		cout << "step5 - fillSpace..." << endl;
		fill2dSpace();
		cout << "DONE!" << endl;
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

void CircullarInclusionsAddition::setUnmixedGrid3D()
{
	int width = 0;

	double translation;
	double amountInRowX = (double)xSize / (2 * radius);
	double amountInRowY = (double)ySize / (2 * radius);
	double amountInRowZ = (double)zSize / (2 * radius);

	int sizeBallsX = (int)amountInRowX + 1;
	int sizeBallsY = (int)amountInRowY + 1;
	int sizeBallsZ = (int)amountInRowZ + 1;

	int* tableOfBallsX = new int[sizeBallsX];
	int* tableOfBallsY = new int[sizeBallsY];
	int* tableOfBallsZ = new int[sizeBallsZ];

	for (int i = 0; i < sizeBallsX; i++)
	{
		translation = amountInRowX - (int)amountInRowX;
		tableOfBallsX[i] = i * 2 * radius + ((int)(translation * radius));
	}
	for (int i = 0; i < sizeBallsY; i++)
	{
		translation = amountInRowY - (int)amountInRowY;
		tableOfBallsY[i] = i * 2 * radius + ((int)(translation * radius));
	}
	for (int i = 0; i < sizeBallsZ; i++)
	{
		translation = amountInRowZ - (int)amountInRowZ;
		tableOfBallsZ[i] = i * 2 * radius + ((int)(translation * radius));
	}

	int portion = sizeBallsX / 3;

	for (int i = 0; i < sizeBallsZ; i++) //here
	{
		for (int j = 0; j < sizeBallsY; j++)
		{
			for (int k = 0; k < sizeBallsX; k++)
			{
				//if(k < ((tableOfCoordsZ.Length / 2) - width) || k > ((tableOfCoordsZ.Length / 2) + width))
				//if (k == 11 || k == 5 || k == 16)
				//if(j == 5 || j == 11 || j == 16)
				//if(i == j || i == j + 10 || i == j - 10)
				//if(ListOfBalls.Count <= 5){
				Ball ball(tableOfBallsX[k], tableOfBallsY[j], tableOfBallsZ[i]);
				balls.push_back(ball);
				//}
				//Console.WriteLine("Checkpoint");
			}
		}
	}
	delete[] tableOfBallsX;
	delete[] tableOfBallsY;
	delete[] tableOfBallsZ;
}

void CircullarInclusionsAddition::addMinimumAmountOfCircles()
{
	double actualSurface = 0;
	double pattern = (acos(-1.0) * pow(radius, 2));
	while (desiredSurface > actualSurface)
	{
		if (balls.size() == 0)
			break;
		int i = rand() % balls.size();
		auto ball = balls[i];
		ball.setRadius(rand() % (radius - 5) + 6); //= rand.Next(6, Radius + 1);
		actualSurface = actualSurface + surface->countArea(ball.getX(), ball.getY(), ball.getRadius());
		activeBalls.push_back(ball);
		balls.erase(balls.begin()+i);
	}
}

void CircullarInclusionsAddition::setBalls3D()
{
	Volume volume(radius, xSize, ySize, zSize);
	int totalVolume = xSize * ySize * zSize;
	int randomindex;
	do
	{
		randomindex = rand() % balls.size(); //rand.Next(0, balls.size());
		ballDirectionInitializer(balls[randomindex]);
		activeBalls.push_back(balls[randomindex]);
		volume.countVolume(radius, balls[randomindex].getX(), balls[randomindex].getY(), balls[randomindex].getZ());
		balls.erase(balls.begin() + randomindex);
	} while (volume.getActualVolume() < (totalVolume)* desiredVolume / 100 && balls.size() > 0);
}

void CircullarInclusionsAddition::adjustSurface()
{
	int actualSurface = 0;
	for (auto &activeBall : activeBalls)
	{
		activeBall.setRadius(rand() % radius +1); //= rand.Next(1, Radius + 1);
		actualSurface = actualSurface + surface->countArea(activeBall.getX(), activeBall.getY(), activeBall.getRadius());
	}
	while (actualSurface < desiredSurface)
	{
		if (balls.size() > 0)
		{
			if (rand() % 2 == 1)
			{
				int i = rand() % balls.size();
				auto ball = balls[i];
				ball.setRadius(rand() % radius + 1); //= rand.Next(1, radius + 1);
				actualSurface = actualSurface + surface->countArea(ball.getX(), ball.getY() , ball.getRadius());
				activeBalls.push_back(ball);
				balls.erase(balls.begin()+i);
			}
			else
			{
				vector<Ball> temp;
				for (auto &activeBall : activeBalls)
				{
					if (activeBall.getX() != radius)
					{
						temp.push_back(activeBall);
					}
				}
				auto ball = temp[rand() % temp.size()];
				actualSurface = actualSurface - surface->countArea(ball.getX(), ball.getY(), ball.getRadius());
				ball.setRadius(rand() % (radius+1-ball.getRadius())+ ball.getRadius()); // = rand.Next(circle.radius, Radius + 1);
				actualSurface = actualSurface + surface->countArea(ball.getX(), ball.getY(), ball.getRadius());
			}
		}
		else
		{
			vector<Ball> temp;
			for (auto &activeBall : activeBalls)
			{
				if (activeBall.getX() != radius)
				{
					temp.push_back(activeBall);
				}
			}
			auto ball = temp[rand() % temp.size()];
			actualSurface = actualSurface - surface->countArea(ball.getX(), ball.getY(), ball.getRadius());
			ball.setRadius(rand() % (radius + 1 - ball.getRadius()) + ball.getRadius()); // = rand.Next(circle.radius, Radius + 1);
			actualSurface = actualSurface + surface->countArea(ball.getX(), ball.getY(), ball.getRadius());
		}
	}
}

void CircullarInclusionsAddition::mixBalls2D()
{
	
	Ball movedBall;
	for (auto &activeBall : activeBalls)
	{
		Direction randomDir = static_cast<Direction>(rand() % 2 + 1);  //rand.Next(1, 3); //list[(rand.Next(list.Count))];
		activeBall.setDirX(randomDir);
		randomDir = static_cast<Direction>(rand() % 2 + 3); //rand.Next(3, 5);
		activeBall.setDirY(randomDir);
	}
	for (int i = 0; i < 100; i++)
	{
		for (auto &activeBall : activeBalls)
		{
			Direction dir;
			bool side;
			movedBall = Ball(activeBall.getX(), activeBall.getY(), activeBall.isSide(),activeBall.getRadius(), activeBall.getDirX(), activeBall.getDirY());

			if ((movedBall.getX() + movedBall.getRadius() >= xSize || movedBall.getX() - movedBall.getRadius() < 0) &&
				(movedBall.getY() + movedBall.getRadius() >= ySize || movedBall.getY() - movedBall.getRadius() < 0))
			{
				continue;
			}
			else if (movedBall.getX() + movedBall.getRadius() >= xSize || movedBall.getX() - movedBall.getRadius() < 0)
			{
				movedBall.setY(movedBall.getY() + (movedBall.getDirY() == Up ? 1 : -1));
				dir = activeBall.getDirY() == Up ? Down : Up;
				activeBall.setDirY(dir);
			}
			else if (movedBall.getY() + movedBall.getRadius() >= ySize || movedBall.getY() - movedBall.getRadius() < 0)
			{
				movedBall.setX(movedBall.getX() + (movedBall.getDirX() == Left ? -1 : 1));
				dir = activeBall.getDirX() == Left ? Right : Left;
				activeBall.setDirX(dir);
			}
			else
			{
				if (rand() %2 == 1)
				{
					side = true;
				}
				else
				{
					side = false;
				}
				if (side == true)
				{
					movedBall.setX(movedBall.getX() + (movedBall.getDirX() == Left ? -1 : 1));
					dir = activeBall.getDirX();

				}
				else
				{
					movedBall.setY(movedBall.getY() + (movedBall.getDirY() == Up ? 1 : -1));

					dir = activeBall.getDirY();
				}

			}
			if (checkIfInRange(movedBall, dir))
			{
				switch (dir)
				{
				case Left:

					activeBall.setDirX(Right);
					break;
				case Right:
					activeBall.setDirX(Left);
					break;
				case Up:
					activeBall.setDirX(Down);
					break;
				case Down:
					activeBall.setDirX(Up);
					break;
				default:
					break;
				}
			}
			else
			{
				activeBall = movedBall;
			}
		}
	}
}

void CircullarInclusionsAddition::mixBalls3D()
{
	int counter = 0;
	Ball movedBall;
	for (int i = 0; i <200/* radius + (radius / 2)*/; i++)
	{
		for (auto &activeBall : activeBalls)
		{
			movedBall = Ball(
				activeBall.getX()
				,activeBall.getY()
				,activeBall.getZ()
				,activeBall.getDirX()
				,activeBall.getDirY()
				,activeBall.getDirZ()
			);
			
			moveBall(movedBall);
			if (checkIfInRange(movedBall))
			{
				directionSetter(movedBall, activeBall);
			}
			else
			{
				counter++;
				//if(movedBall.z)
				activeBall = movedBall;
			}
		}

	}
}

void CircullarInclusionsAddition::reduceBalls3D()
{
	cout << "Pre-Globules: " << activeBalls.size() << endl;

	while (activeBalls.size() > 260)
	{
		int randomIdx = rand() % activeBalls.size();
		activeBalls.erase(activeBalls.begin() + randomIdx);
	}

	cout << "Post-Globules: " << activeBalls.size() << endl;
}

bool CircullarInclusionsAddition::checkIfInRange(Ball movedBall, Direction dir)
{
	int rangexd = movedBall.getX() + 2 * radius;
	int rangexu = movedBall.getX() - 2 * radius;
	int rangeyd = movedBall.getY() + 2 * radius;
	int rangeyu = movedBall.getY() - 2 * radius;
	bool isBallinRange = false;
	int xtranslation = 0;
	int ytranslation = 0;
	if (dir == Up)
	{
		ytranslation = 1;
	}
	else if (dir == Down)
	{
		ytranslation = -1;
	}
	else
	{
		if (dir == Left)
		{
			xtranslation = -1;
		}
		else if (dir == Right)
		{
			xtranslation = 1;
		}
	}

	for(auto &activeBall : activeBalls)
	{

		if (((activeBall.getX() >= rangexu && activeBall.getX() <= rangexd) ||
			(activeBall.getY() >= rangeyu && activeBall.getY() <= rangeyd)))
		{
			//TODO: Mozna zrezygnowac z tego ifa
			if (activeBall.isSide() != movedBall.isSide())
			{
				if (!(activeBall.getX() == movedBall.getX() - xtranslation && activeBall.getY() == movedBall.getY() - ytranslation))
				{
					if (!(sqrt(pow(activeBall.getX() - movedBall.getX(), 2) + pow(activeBall.getY() - movedBall.getY(), 2)) >= activeBall.getRadius() + movedBall.getRadius() + 2))
					{
						return true;
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (!(activeBall.getX() == movedBall.getX() - xtranslation && activeBall.getY() == movedBall.getY() - ytranslation))
				{
					if (!(sqrt(pow(activeBall.getX() - movedBall.getX(), 2) + pow(activeBall.getY() - movedBall.getY(), 2)) >= radius * 2 + 2))
					{
						return true;
					}
				}
				else
				{
					continue;
				}
			}
		}
	}
	return false;
}

bool CircullarInclusionsAddition::checkIfInRange(Ball movedBall)
{
	int ballsinrange = 0;
	int rangexd = movedBall.getX() + 2 * radius;
	int rangexu = movedBall.getX() - 2 * radius;
	int rangeyd = movedBall.getY() + 2 * radius;
	int rangeyu = movedBall.getY() - 2 * radius;
	int rangezd = movedBall.getZ() + 2 * radius;
	int rangezu = movedBall.getZ() - 2 * radius;
	if ((movedBall.getX() + radius >= xSize || movedBall.getX() - radius < 0) && movedBall.getDirX() != Immovable)
		return true;
	if ((movedBall.getY() + radius >= ySize || movedBall.getY() - radius < 0) && movedBall.getDirY() != Immovable)
		return true;
	if ((movedBall.getZ() + radius >= zSize || movedBall.getZ() - radius < 0) && movedBall.getDirZ() != Immovable)
		return true;
	for(auto &ball : activeBalls)
	{
		if (((ball.getX() >= rangexu && ball.getX() <= rangexd) ||
			(ball.getY() >= rangeyu && ball.getY() <= rangeyd)
			|| (ball.getZ() >= rangezu && ball.getZ() <= rangezd)))
		{
			if (sqrt(pow(ball.getX() - movedBall.getX(), 2) + pow(ball.getY() - movedBall.getY(), 2)
				+ pow(ball.getZ() - movedBall.getZ(), 2)) >= 2 * radius)
			{
				continue;
			}
			else
			{
				ballsinrange++;
				if (ballsinrange > 1)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void CircullarInclusionsAddition::fill2dSpace()
{
	int currentId = 1;
	vector<BallSchema2D*> ballSchemas;
	for (auto &activeBall : activeBalls)
	{
		BallSchema2D* schema = nullptr;
		for (auto &ballSchema : ballSchemas)
		{
			if (ballSchema->getSize() == activeBall.getRadius() * 2)
			{
				schema = ballSchema;
				break;
			}
		}
		if (schema == nullptr) 
		{
			schema = create2DSchema(activeBall.getRadius());
			ballSchemas.push_back(schema);
		}
		fill2dBall(schema, activeBall.getX(), activeBall.getY(), activeBall.getRadius(), currentId);
		currentId++;
	}
}

void CircullarInclusionsAddition::fill3dSpace()
{
	int currentId = 1;
	for (auto &ball : activeBalls)
	{
		auto startx = ball.getX() - radius > 0 ? ball.getX() - radius : 0;
		auto endx = ball.getX() + radius < xSize ? ball.getX() + radius : xSize;
		auto starty = ball.getY() - radius > 0 ? ball.getY() - radius : 0;
		auto endy = ball.getY() + radius <0 ? ball.getY() + radius : ySize;
		auto startz = ball.getZ() - radius > 0 ? ball.getZ() - radius : 0;
		auto endz = ball.getZ() + radius < 0 ? ball.getZ() + radius : zSize;
		for (int i = startx; i < endx; i++)
		{
			for (int j = starty; j < endy; j++)
			{
				for (int k = startz; k < endz; k++)
				{
					if (sqrt(pow(ball.getX() - i, 2) + pow(ball.getY() - j, 2)
						+ pow(ball.getZ() - k, 2)) <= radius) 
					{
						this->space->getCells()[i][j][k]->setId(currentId);
						this->space->getCells()[i][j][k]->setPhase(Inclusion);
					}
				}
			}
		}
		currentId++;
	}
}

BallSchema2D * CircullarInclusionsAddition::create2DSchema(int radius)
{
	int ballMiddle = radius;
	BallSchema2D* schema = new BallSchema2D(radius);
	for (int i = 0; i < schema->getSize() / 2; i++)
	{
		for (int j = 0; j < schema->getSize() / 2; j++)
		{
			double pierw = sqrt(pow(radius - i, 2) + pow(radius - j, 2));
			if (pierw < radius)
			{
				schema->getSchema()[i][j] = true;
			}
		}
	}
	for (int i = radius; i < schema->getSize(); i++)
	{
		for (int j = 0; j < schema->getSize() / 2; j++)
		{
			schema->getSchema()[schema->getSize() - (i - radius) - 1][j] = schema->getSchema()[i - radius][j];
		}
	}
	for (int i = 0; i < schema->getSize(); i++)
	{
		for (int j = radius; j < schema->getSize(); j++)
		{
			schema->getSchema()[i][j] = schema->getSchema()[i][schema->getSize() - j - 1];
		}
	}
	return schema;
}

void CircullarInclusionsAddition::fill2dBall(BallSchema2D *schema, int x, int y, int radius, int id)
{
	for (int i = 0; i < schema->getSize(); i++)
	{
		for (int j = 0; j < schema->getSize(); j++)
		{
			if (!(x + i - radius >= xSize || x + i - radius < 0 || y + j - radius >= ySize || y + j - radius < 0))
			{
				if (this->space->getCells()[x + i - radius][y + j - radius][0]->getPhase() != Inclusion)
				{
					if (schema->getSchema()[i][j])
					{
						this->space->getCells()[x + i - radius][y + j - radius][0]->setId(id);
						this->space->getCells()[x + i - radius][y + j - radius][0]->setPhase(Inclusion);
					}
				}
			}
		}
	}
}

void CircullarInclusionsAddition::ballDirectionInitializer(Ball &ball)
{
	bool isOnBoundary = false;
	if (ball.getX() + radius >= xSize)
	{
		isOnBoundary = true;
		ball.setDirX(Immovable);
		ball.setX(ball.getX() + rand()% radius);
	}
	if (ball.getX() - radius < 0)
	{
		isOnBoundary = true;
		ball.setDirX(Immovable);
		ball.setX(ball.getX() - rand() % radius);
	}
	if (ball.getY() + radius >= ySize)
	{
		isOnBoundary = true;
		ball.setDirY(Immovable);
		ball.setY(ball.getY() + rand() % radius);
	}
	if (ball.getY() - radius < 0)
	{
		isOnBoundary = true;
		ball.setDirY(Immovable);
		ball.setY(ball.getY() - rand() % radius);
	}
	if (ball.getZ() + radius >= zSize)
	{
		isOnBoundary = true;
		ball.setDirZ(Immovable);
		ball.setZ(ball.getZ() + rand() % radius);
	}
	if (ball.getZ() - radius < 0)
	{
		isOnBoundary = true;
		ball.setDirZ(Immovable);
		ball.setZ(ball.getZ() - rand() % radius);
	}
	if (!isOnBoundary)
	{
		ball.setDirX(xSize / 2 > ball.getX() ? Left : Right);
		ball.setDirY(ySize / 2 > ball.getY() ? Down : Up);
		ball.setDirZ(zSize / 2 > ball.getZ() ? Forward : Backward);
	}
}

void CircullarInclusionsAddition::directionSetter(Ball &ball, Ball &notMovedBall)
{
	if (ball.getX() != notMovedBall.getX()&&notMovedBall.getDirX() != Immovable)
		notMovedBall.setDirX(notMovedBall.getDirX() == Left ? Right :Left);
	else if (ball.getY() != notMovedBall.getY() && notMovedBall.getDirY() != Immovable)
		notMovedBall.setDirY(notMovedBall.getDirY() == Up ? Down : Up);
	else if (ball.getZ() != notMovedBall.getZ() && notMovedBall.getDirZ() != Immovable)
		notMovedBall.setDirZ(notMovedBall.getDirZ() == Forward ? Backward : Forward);
}

void CircullarInclusionsAddition::moveBall(Ball &ball)
{
	switch (rand() % 3 + 1 )
	{
	case 1:
		if (ball.getDirX() != Immovable)
			ball.setX(ball.getDirX() == Left ? ball.getX() - 1 : ball.getX() + 1);
		break;
	case 2:
		if (ball.getDirY() != Immovable)
			ball.setY(ball.getDirY() == Up ? ball.getY() + 1 : ball.getY() - 1);
		break;
	case 3:
		if (ball.getDirZ() != Immovable)
			ball.setZ(ball.getDirZ() == Forward ? ball.getZ() - 1 : ball.getZ() + 1);
		break;
	default:
		break;
	}
}

int CircullarInclusionsAddition::getProgress()
{
	return progress;
}

vector<Ball> CircullarInclusionsAddition::getActiveBalls()
{
	return activeBalls;
}

vector<Ball> CircullarInclusionsAddition::getBalls()
{
	return balls;
}