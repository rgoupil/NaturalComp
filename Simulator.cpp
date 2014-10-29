#include "Simulator.h"

Simulator::Simulator(Algorithm & algorithm)
{
	pAlgorithm = &algorithm;
}

void Simulator::initialize(void)
{
	pCycleCount = 0;
	pTime = 0.0;

	pAlgorithm->initialize();
}

bool Simulator::step(void)
{
	bool success;
	success = pAlgorithm->update(pCycleCount, pTime);
	if (pCycleEndFunc)
	{
		pCycleEndFunc(pCycleCount, pTime);
	}
	
	pCycleCount++;

	return success;
}

void Simulator::simulate(unsigned int cyclesToRun /*= -1*/)
{
	bool shouldStop = false;

	for (unsigned int i = 0; (i == static_cast<unsigned int>(-1) || i < cyclesToRun) && !shouldStop; i++)
	{
		shouldStop = !step();
	}
}

void Simulator::setCycleEndCallback(const t_endcycle_func & func)
{
	pCycleEndFunc = func;
}