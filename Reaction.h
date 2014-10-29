#ifndef Reaction_h_
#define Reaction_h_

#include <functional>

class Reaction
{
public:
	typedef std::function<void(Reaction & reaction)> t_init_func;
	typedef std::function<bool(Reaction & reaction, unsigned int, double)> t_eval_func;
	typedef std::function<double(Reaction & reaction)> t_rate_func;
	typedef std::function<double(Reaction & reaction)> t_propensity_func;

	Reaction(const t_init_func & initFunc,
		const t_eval_func & evalFunc,
		const t_rate_func & rateFunc,
		const t_propensity_func & propFunc);

	void initialize(void);
	bool evaluate(unsigned int cycleCount, double deltaTime);
	double getRate(void);
	double getPropensity(void);

protected:
	t_init_func pInitFunction;
	t_eval_func pEvalFunction;
	t_rate_func pRateFunction;
	t_propensity_func pPropFunc;
};

#endif