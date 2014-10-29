#ifndef Simulator_h_
#define Simulator_h_

#include "Parameter.h"
#include "Algorithm.h"

#include <functional>

class Simulator
{
public:
	typedef std::function<void(unsigned int, double)> t_endcycle_func;

	Simulator(Algorithm & algorithm);
	void initialize(void);
	bool step(void);
	void simulate(unsigned int cyclesToRun = -1);

	void setCycleEndCallback(const t_endcycle_func & func);

protected:
	Algorithm * pAlgorithm;
	unsigned int pCycleCount;
	double pTime;
	t_endcycle_func pCycleEndFunc;
};

#endif