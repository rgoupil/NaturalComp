#include "Simulation.h"

void Simulation::initialize(void)
{
	pAlgorithm = 0x0;

	pInitialize();

	pSimulator = new Simulator(*pAlgorithm);
	pSimulator->initialize();
	pSimulator->setCycleEndCallback([this](unsigned int c, double t) {
		pOnEndCycle(c, t);
	});
}

void Simulation::simulate(unsigned int cyclesToRun /*= 0*/)
{
	pSimulator->simulate(cyclesToRun);
}

void Simulation::pOnEndCycle(unsigned int cycleCount, double currentTime)
{ }