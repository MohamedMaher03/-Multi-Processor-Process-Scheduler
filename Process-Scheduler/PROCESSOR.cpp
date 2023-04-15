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

void PROCESSOR::ResetRunningProcess(int x)
{
	if (RUN)
	{
		if (RUN->get_PID() == x)
		{
			STATE = 0;
			RUN = nullptr;
		}
	}
	
}

void PROCESSOR::setRunningInSched(int x)
{
	if (!x)
	{
		RunningInSched = false;
		return;
	}
	RunningInSched = true;
}

bool PROCESSOR::getRunningInSched()
{
	return RunningInSched;
}

PROCESSOR::PROCESSOR()
{ 
	ProcessorLoad = 0;
	ProcessorUtilization = 0;
	RSIZE = 0;
	RUN = nullptr;
	RunningInSched = false;
}
