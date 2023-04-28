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
void PROCESSOR:: setState(bool s) {
	STATE = s;
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
			RunningInSched = 0;
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

int PROCESSOR::getExpectedFinishTime()
{
	return ExpectedFinishTime;
}

PROCESSOR::PROCESSOR()
{ 
	ExpectedFinishTime = 0;
	PLoad = 0;
	PUtil = 0;
	RSIZE = 0;
	RUN = nullptr;
	RunningInSched = false;
}

PROCESSOR::~PROCESSOR()
{
}
