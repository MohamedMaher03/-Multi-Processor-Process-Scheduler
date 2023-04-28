#include "SJF.h"



SJF::SJF(Scheduler* scheduler)
{
	STATE = 0;
	RUN = nullptr;
	TYPE = "SJF";
	RSIZE = 0;
	SchedPtr = scheduler;
}


void SJF::ScheduleAlgo()
{
	
	if (!STATE)  //if the processor is IDLE 
	{
		PROCESS* HighestPriorityPROCESS;
		if (RDY.dequeue(HighestPriorityPROCESS)) {
			RUN = HighestPriorityPROCESS;
			RUN->set_starttime(SchedPtr->get_TIMESTEP());  //set start time if process didn't start CPU before 
			STATE = 1;
		}
	}
	else {
		// if there is a process running in the CPU

		if (SchedPtr->Process_completion(RUN))
		{
			RUN = nullptr;
			STATE = 0;
		}
		else if (SchedPtr->IO_requesthandling(RUN))
		{
			RUN = nullptr;
			STATE = 0;
		}
		else {
			RUN->incrementCountsteps(1);
		}
	}
}

void SJF::addToMyRdy(PROCESS* process)
{
	RDY.enqueue(process, process->get_CT());
	RSIZE++;
}

bool SJF::PromoteProcess(int x)
{
	if (!STATE && !RDY.isEmpty())// the processor is IDLE
	{
		PROCESS* toberun;
		//If RDY.peek() exists I want to check if the timestep is equal AT, if this is the case return false
		if (RDY.peek(toberun))
			if (x == toberun->get_AT())
				return false;
		if (RDY.dequeue(toberun))
		{
			RUN = toberun;
			STATE = 1;
			RSIZE--;
			return true;
		}
	}
	return false;
}

void  SJF::PrintMyReady() 
{
	RDY.printContents();
}

