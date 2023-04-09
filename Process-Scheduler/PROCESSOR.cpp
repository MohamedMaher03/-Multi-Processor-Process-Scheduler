#include "PROCESSOR.h"
#include <iostream>

void PROCESSOR::PrintMyReady()
{
	RDY.printContents();
}

int PROCESSOR::getRSIZE()
{
	return RSIZE;
}

PROCESS* PROCESSOR::getCurrentlyRunning()
{
	return RUN;
}
PROCESSOR::PROCESSOR(string type)
{
	RUN = NULL; //Initially no processes are running. 
	STATE = 0;
	TYPE = type; // assign processor type to given type
}
