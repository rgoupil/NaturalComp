#include "Simulation2.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

Simulation2::Simulation2(std::vector<std::string> & log)
	: pLog(log)
{
}

void Simulation2::pInitialize(void)
{
	Gillespie * gillespie = new Gillespie();

	pSetupSimulation();

	for (unsigned int i = 0; i < pReactions.size(); i++)
	{
		gillespie->addReaction(pReactions[i]);
	}

	pAlgorithm = gillespie;

	std::stringstream ss;
	ss << "# Generated graph of a molecule simulation" << std::endl;
	ss << "# Time\tA-Count\tB-Count" << std::endl;
	pLog.push_back(ss.str());
}

void Simulation2::pSetupSimulation(void)
{
	double ka = 1.0;
	double Ka = 1.0;
	double kb = 1.0;
	double Kb = 1.0;
	double db = 0.0001;
	double da = 0.0001;
	double h = 1.0;
	double l = 1.0;

	pMolecules["A"] = { 100 };
	pMolecules["B"] = { 100 };

	Reaction reactionVoid2B(
		[](Reaction & reaction) -> void {},
		[this](Reaction & reaction, unsigned int cycleCount, double deltaTime) -> bool {
		pMolecules["B"].count += 1;
		return true;
	},
		[this, kb, Kb, Ka, h, l](Reaction & reaction) -> double {
		double ah = std::pow(pMolecules["A"].count, h);
		double bl = std::pow(pMolecules["B"].count, l);
		return kb * ((ah * Kb) / ((Ka + ah) * (Kb + bl)));
	},
		[](Reaction & reaction) -> double {
		return reaction.getRate();
	});

	Reaction reactionB2Void(
		[](Reaction & reaction) -> void {},
		[this](Reaction & reaction, unsigned int cycleCount, double deltaTime) -> bool {
		pMolecules["B"].count -= 1;
		return true;
	},
		[db](Reaction & reaction) -> double {
		return db;
	},
		[this](Reaction & reaction) -> double {
		return reaction.getRate() * pMolecules["B"].count;
	});

	Reaction reactionVoid2A(
		[](Reaction & reaction) -> void {},
		[this](Reaction & reaction, unsigned int cycleCount, double deltaTime) -> bool {
		pMolecules["A"].count += 1;
		return true;
	},
		[this, ka, Kb, Ka, h, l](Reaction & reaction) -> double {
		double ah = std::pow(pMolecules["A"].count, h);
		double bl = std::pow(pMolecules["B"].count, l);
		return ka * ((bl * Ka) / ((Ka + ah) * (Kb + bl)));
	},
		[](Reaction & reaction) -> double {
		return reaction.getRate();
	});

	Reaction reactionA2Void(
		[](Reaction & reaction) -> void {},
		[this](Reaction & reaction, unsigned int cycleCount, double deltaTime) -> bool {
		pMolecules["A"].count -= 1;
		return true;
	},
		[da](Reaction & reaction) -> double {
		return da;
	},
		[this](Reaction & reaction) -> double {
		return reaction.getRate() * pMolecules["A"].count;
	});

	pReactions.push_back(reactionVoid2B);
	pReactions.push_back(reactionB2Void);
	pReactions.push_back(reactionVoid2A);
	pReactions.push_back(reactionA2Void);
}

void Simulation2::pOnEndCycle(unsigned int cycleCount, double currentTime)
{
	std::stringstream ss;
	ss << currentTime
		<< "\t" << (float)pMolecules["A"].count
		<< "\t" << (float)pMolecules["B"].count
		<< std::endl;
	pLog.push_back(ss.str());
}