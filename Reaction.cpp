#include "Reaction.h"

Reaction::Reaction(const t_init_func & initFunc,
	const t_eval_func & evalFunc,
	const t_rate_func & rateFunc,
	const t_propensity_func & propFunc)
{
	pInitFunction = initFunc;
	pEvalFunction = evalFunc;
	pRateFunction = rateFunc;
	pPropFunc = propFunc;
}


void Reaction::initialize(void)
{
	pInitFunction(*this);
}

bool Reaction::evaluate(unsigned int cycleCount, double deltaTime)
{
	return pEvalFunction(*this, cycleCount, deltaTime);
}

double Reaction::getRate(void)
{
	return pRateFunction(*this);
}

double Reaction::getPropensity(void)
{
	return pPropFunc(*this);
}