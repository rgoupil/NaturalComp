#include "Simulation3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

Simulation3::Simulation3(std::vector<std::string> & log)
	: pLog(log)
{
}

void Simulation3::pInitialize(void)
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
	ss << "# Time\tA-Count\tB-Count\tC-Count" << std::endl;
	pLog.push_back(ss.str());
}

void Simulation3::pSetupSimulation(void)
{
	double kc = 1.0;
	double h = 16.0;
	double K = 1.0;

	pMolecules["A"] = { 100 };
	pMolecules["B"] = { 142 };
	pMolecules["C"] = { 0 };

	Reaction reactionVoid2C(
		[](Reaction & reaction) -> void {},
		[this](Reaction & reaction, unsigned int cycleCount, double deltaTime) -> bool {
		pMolecules["A"].count -= 1;
		pMolecules["B"].count -= 1;
		pMolecules["C"].count += 1;
		return true;
	},
		[this, kc, h, K](Reaction & reaction) -> double {
		double Ah = std::pow(pMolecules["A"].count, h);
		double Bh = std::pow(pMolecules["B"].count, h);
		double Kh = std::pow(K, h);
		return kc * (Ah / (Ah + Kh)) * (Bh / (Bh + Kh));
	},
		[](Reaction & reaction) -> double {
		return reaction.getRate();
	});

	pReactions.push_back(reactionVoid2C);
}

void Simulation3::pOnEndCycle(unsigned int cycleCount, double currentTime)
{
	std::stringstream ss;
	ss << currentTime
		<< "\t" << (float)pMolecules["A"].count
		<< "\t" << (float)pMolecules["B"].count
		<< "\t" << (float)pMolecules["C"].count
		<< std::endl;
	pLog.push_back(ss.str());
}