#include "PROCESSOR.h"
#include <iostream>

void PROCESSOR::PrintMyReady()
{
	RDY.printContents();
}

PROCESS* PROCESSOR::getCurrentlyRunning()
{
	return RUN;
}
PROCESSOR::PROCESSOR(string type)
{
	RUN = NULL; //Initially no processes are running. 
	TYPE = type; // assign processor type to given type
}
