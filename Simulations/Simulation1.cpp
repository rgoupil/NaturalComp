#include "Simulation1.h"

#include <iostream>
#include <fstream>
#include <sstream>

Simulation1::Simulation1(std::vector<std::string> & log)
	: pLog(log)
{
}

void Simulation1::pInitialize(void)
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
	ss << "# Time\tNormed-AtNormed-B" << std::endl;
	pLog.push_back(ss.str());
}

void Simulation1::pSetupSimulation(void)
{
	pMolecules["A"] = { 199 };
	pMolecules["B"] = { 1 };

	Reaction reactionA2B(
		[](Reaction & reaction) -> void {
	},
		[this](Reaction & reaction, unsigned int cycleCount, double deltaTime) -> bool {
		pMolecules["A"].count -= 1;
		return pMolecules["A"].count > 0;
	},
		[](Reaction & reaction) -> double {
		return 1.0;
	},
		[this](Reaction & reaction) -> double {
		return reaction.getRate() * pMolecules["A"].count * pMolecules["B"].count;
	});

	pReactions.push_back(reactionA2B);
}

void Simulation1::pOnEndCycle(unsigned int cycleCount, double currentTime)
{
	std::stringstream ss;
	double moleculeSum = std::fmax(0.0, pMolecules["A"].count + pMolecules["B"].count);
	ss << currentTime
		<< "\t" << (float)pMolecules["A"].count / moleculeSum
		<< "\t" << (float)pMolecules["B"].count / moleculeSum
		<< std::endl;
	pLog.push_back(ss.str());
}