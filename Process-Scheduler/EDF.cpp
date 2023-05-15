#include "EDF.h"

EDF::EDF(Scheduler* sc) :PROCESSOR(sc)
{
	STATE = 0;
	RUN = nullptr;
	TYPE = "EDF";
	RSIZE = 0;
	PLoad = 0;
	PUtil = 0;
	TotalBusyTime = 0;
}

void EDF::ScheduleAlgo()
{
	if (!RUN)
	
}

void EDF::addToMyRdy(PROCESS* process)
{
	RDY.enqueue(process, process->get_CT());
	ExpectedFinishTime += process->get_CT();
	RSIZE++;
}

bool EDF::PromoteProcess()
{
	if (!STATE && !RDY.isEmpty())// the processor is IDLE
	{
		PROCESS* toberun;
		//If RDY.peek() exists I want to check if the timestep is equal AT, if this is the case return false
		if (RDY.dequeue(toberun))
		{
			RUN = toberun;
			STATE = 1;
			RSIZE--;
			ExpectedFinishTime -= toberun->get_CT();
			return true;
		}
	}
	return false;
}

PROCESS* EDF::removeTopOfMyRDY()
{
	PROCESS* top = nullptr;
	if (RDY.dequeue(top)) {
		ExpectedFinishTime -= top->get_CT();
		RSIZE--;
	}
	return top;
}

void  EDF::PrintMyReady()
{
	RDY.printContents();
}

