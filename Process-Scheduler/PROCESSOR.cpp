#include "PROCESSOR.h"

using namespace std;

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
}
