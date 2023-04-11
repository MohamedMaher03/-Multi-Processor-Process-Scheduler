#include "PROCESSOR.h"

int PROCESSOR::getRSIZE()
{
	return RSIZE;
}

string PROCESSOR::getType()
{
	return TYPE;
}

PROCESS* PROCESSOR::getCurrentlyRunning()
{
	return RUN;
}
bool PROCESSOR::getState()
{
	return STATE;
}

PROCESSOR::PROCESSOR()
{
	RUN = NULL; //Initially no processes are running. 
	STATE = 0;
	ProcessorLoad = 0;
	ProcessorUtilization = 0;
	RSIZE = 0;
}
