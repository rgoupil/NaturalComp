#ifndef Algorithm_h_
#define Algorithm_h_

#include "Parameter.h"

// Interface to implement different algorithm
class Algorithm
{
public:
	virtual void initialize(void) = 0;
	virtual bool update(unsigned int cycleCount, double & currentTime) = 0;
};

#endif