#ifndef Simulation2_h_
#define Simulation2_h_

#include <vector>
#include <string>
#include <map>

#include "Simulation.h"
#include "Reaction.h"
#include "Gillespie.h"

class Simulation2 : public Simulation
{
public:
	Simulation2(std::vector<std::string> & log);

protected:
	struct Molecule
	{
	public:
		unsigned int count;
	};

	virtual void pInitialize(void);
	virtual void pOnEndCycle(unsigned int cycleCount, double currentTime);
	void pSetupSimulation(void);

	std::vector<std::string> & pLog;
	std::map<std::string, Molecule> pMolecules;
	std::vector<Reaction> pReactions;
};

#endif