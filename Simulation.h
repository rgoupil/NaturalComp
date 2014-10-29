#ifndef Simulation_h_
#define Simulation_h_

#include "Simulator.h"

class Simulation
{
public:
	virtual void initialize(void);
	virtual void simulate(unsigned int cyclesToRun = -1);

protected:
	virtual void pInitialize(void) = 0;
	virtual void pOnEndCycle(unsigned int cycleCount, double currentTime);

	Simulator * pSimulator;
	Algorithm * pAlgorithm;
};

#endif