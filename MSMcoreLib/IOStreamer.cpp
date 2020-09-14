#include "IOStreamer.h"
#include <iterator>
#include <regex>
#include <sstream>
#include "Neighborhood2DVonNeumann.h"
#include "Neighborhood3DVonNeumann.h"


void IOStreamer::SaveSpace(Space* space, string path)
{
	ofstream out(path);
	auto xSize = space->getXsize();
	auto ySize = space->getYsize();
	auto zSize = space->getZsize();
	auto neighborhood = space->getNeighborhood()->getNeighborhoodType();
	auto bc = space->getBoundaryConditions();
	auto r = 0;

	out << "//Space" << ";" << xSize << ";" << ySize << ";" << zSize << ";" << neighborhood << ";" << bc << ";" << r << endl;

	out << "//x;y;z;id;phase;isBorder;canGrowth" << endl;
	for (auto i = 0; i < xSize; i++)
	{
		for (auto j = 0; j < ySize; j++)
		{
			for (auto k = 0; k < zSize; k++)
			{
				Cell* cell = space->getCells()[i][j][k];
				out << i << ";" << j << ";" << k << ";" << cell->getId() << ";" << cell->getPhase() << ";" << cell->getIsBorder() << ";" << cell->getCanGrowth() << endl;
			}	
		}
	}

	out.close();
}

void IOStreamer::LoadSpace(Space* space, string path)
{
	ifstream infile(path);
	string line;
	string commentary = "//";
	getline(infile, line); //ignore space size
	while (getline(infile, line))
	{
		if (line.substr(0, commentary.size()) == commentary) continue;

		replace(line.begin(), line.end(), ';', ' ');
		vector<string> result;
		istringstream iss(line);
		for (string l; iss >> l; )
			result.push_back(l);

		Point * p = new Point(stoi(result[0]), stoi(result.at(1)), stoi(result.at(2)));
		Cell * c = space->getCell(p);

		c->setId(stoi(result.at(3)));
		//c->setPhase(static_cast<Phase>(stoi(result.at(4))));
		//c->setIsBorder(stoi(result.at(5)));
		//c->setCanGrowth(stoi(result.at(6)));
	}
}