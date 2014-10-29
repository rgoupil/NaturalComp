#ifndef Gillespie_h_
#define Gillespie_h_

#include <vector>
#include <map>
#include <string>
#include <random>

#include "Algorithm.h"
#include "Reaction.h"

class Gillespie : public Algorithm
{
public:
	Gillespie(void);
	virtual void initialize(void);
	virtual bool update(unsigned int cycleCount, double & currentTime);
	virtual void addReaction(const Reaction & reaction);

protected:
	typedef std::vector<std::pair<double, unsigned int>> t_propensities_type;

	virtual double pComputeDeltaTime(void);
	virtual void pComputePropensities(t_propensities_type & propensities);
	virtual Reaction * pSelectReaction(const t_propensities_type & propensities);

protected:
	std::default_random_engine pGenerator;
	std::uniform_real_distribution<float> pTimeDistribution;
	std::uniform_real_distribution<float> pPropensityDistribution;
	std::vector<Reaction> pReactionList;
};

#endif