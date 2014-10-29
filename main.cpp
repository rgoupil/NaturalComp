
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Simulation.h"
#include "Simulation1.h"
#include "Simulation2.h"
#include "Simulation3.h"

int main(int argc, const char *argv[])
{
	std::vector<std::string> log;

	// Change the simulation to run here
	//Simulation * simulation = new Simulation1(log);
	//Simulation * simulation = new Simulation2(log);
	Simulation * simulation = new Simulation3(log);
	simulation->initialize();
	simulation->simulate(200);

	std::ofstream outputLog("log.dat", std::ios_base::out | std::ios_base::trunc);
	if (outputLog.is_open())
	{
		for (unsigned int i = 0; i < log.size(); i++)
		{
			outputLog.write(log[i].c_str(), log[i].size());
		}

		outputLog.close();
	}

	return 0;
}