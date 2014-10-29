#include <chrono>
#include <math.h>
#include <algorithm>

#include "Gillespie.h"

Gillespie::Gillespie(void)
	: pTimeDistribution(0.0), pPropensityDistribution(0.0f, 1.0f)
{
}

void Gillespie::initialize(void)
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	pGenerator.seed(static_cast<unsigned long>(seed));

	for (unsigned int i = 0; i < pReactionList.size(); i++)
	{
		pReactionList[i].initialize();
	}
}

bool Gillespie::update(unsigned int cycleCount, double & currentTime)
{
	if (pReactionList.size() <= 0)
	{
		return false;
	}

	t_propensities_type propensities;

	double deltaTime = pComputeDeltaTime();
	pComputePropensities(propensities);
	Reaction * currentReaction = pSelectReaction(propensities);

	currentTime += deltaTime;

	if (currentReaction == 0x0)
	{
		// No reaction is supposed to happen.
		// This probably mean we have a dead simulation but we handle it.
		return true;
	}

	// Evaluate the reaction
	return currentReaction->evaluate(cycleCount, deltaTime);
}

void Gillespie::addReaction(const Reaction & reaction)
{
	this->pReactionList.push_back(reaction);
}

double Gillespie::pComputeDeltaTime(void)
{
	// Compute the time before the next reaction
	double rateSum = 0.0;
	for (unsigned int i = 0; i < pReactionList.size(); i++)
	{
		rateSum += pReactionList[i].getRate();
	}
	if (rateSum == 0.0)
	{
		rateSum = 1.0;
	}

	float random = pTimeDistribution(pGenerator);
	return -(1.0 / rateSum) * std::log(random);
}

static bool pairCompare(const std::pair<double, unsigned int> & firstElem, const std::pair<double, unsigned int> & secondElem)
{
	return firstElem.first > secondElem.first;
}

void Gillespie::pComputePropensities(t_propensities_type & propensities)
{
	double * props = new double[pReactionList.size()];
	double propensitySum = 0.0;

	// Retreive the propensities and compute their sum
	for (unsigned int i = 0; i < pReactionList.size(); i++)
	{
		double propensity = pReactionList[i].getPropensity();
		props[i] = propensity;
		propensitySum += propensity;
	}

	// Normalize the propensities
	for (unsigned int i = 0; i < pReactionList.size(); i++)
	{
		if (props[i] > 0.0)
		{
			props[i] /= propensitySum;
			propensities.push_back({ props[i], i });
		}
	}

	if (propensities.size() > 1)
	{
		std::sort(propensities.begin(), propensities.end(), pairCompare);
	}
}

Reaction * Gillespie::pSelectReaction(const t_propensities_type & propensities)
{
	// Return the first reaction if there is no other reactions listed
	if (propensities.size() == 1)
	{
		return &pReactionList[propensities[0].second];
	}

	// Select all the reactions that should be selected
	// just in case we have multiple reactions with the same propensity
	double random = pPropensityDistribution(pGenerator);
	for (auto kvp = propensities.begin(); kvp != propensities.end(); ++kvp)
	{
		double propSum = 0.0;
		double propSum2 = 0.0;
		for (auto it = kvp; it != propensities.end(); ++it)
		{
			propSum += it->first;
			if (it > kvp)
			{
				propSum2 += it->first;
			}
		}
		if (random <= propSum && random > propSum2)
		{
			return &pReactionList[kvp->second];
		}
	}

	return 0x0;
}