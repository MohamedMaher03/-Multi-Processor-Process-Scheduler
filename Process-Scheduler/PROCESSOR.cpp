#include "PROCESSOR.h"
#include <iostream>

void PROCESSOR::PrintMyReady()
{
	RDY.printContents();
}

void PROCESSOR::addToMyRdy(PROCESS*add)
{
	RDY.enqueue(add);
}

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
void PROCESSOR::PromoteProcess()
{
	if (!STATE)// the processor is IDLE
	{
		PROCESS* toberun;
		if (RDY.dequeue(toberun))
			RUN = toberun;
		
	}
}
PROCESSOR::PROCESSOR(string type)
{
	RUN = NULL; //Initially no processes are running. 
	STATE = 0;
	TYPE = type; // assign processor type to given type
}
