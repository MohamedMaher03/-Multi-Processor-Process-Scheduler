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
		TotalIdleTime++;
	else
		TotalBusyTime++;

	if (!RUN && RDY.isEmpty())
		return;
	if (!RUN && !RDY.isEmpty())  //if the processor is IDLE 
	{
		PROCESS* HighestPriorityPROCESS;
		if (RDY.dequeue(HighestPriorityPROCESS)) 
		{
			RUN = HighestPriorityPROCESS;
			RUN->set_starttime(SchedPtr->get_TIMESTEP());//set start time if process didn't start CPU before 
			STATE = 1;
			RSIZE--;
			ExpectedFinishTime -= HighestPriorityPROCESS->getlastCT();
			SchedPtr->increment_runningcount();
			if (HighestPriorityPROCESS->get_RT() == -1)
				HighestPriorityPROCESS->set_RT(SchedPtr->get_TIMESTEP() - HighestPriorityPROCESS->get_AT());
		}
	}
	else {	// if there is a process running in the CPU
		PROCESS* HighestPriorityPROCESS;
		if (RDY.peek(HighestPriorityPROCESS) && RUN) {
			if (RUN->get_deadline() > HighestPriorityPROCESS->get_deadline()) {
				addToMyRdy(RUN);
				RUN = nullptr;
				RDY.dequeue(HighestPriorityPROCESS);
				RSIZE--;
				ExpectedFinishTime -= HighestPriorityPROCESS->getlastCT();
				RUN = HighestPriorityPROCESS;
			}
		}

		if (SchedPtr->Process_completion(RUN))
		{
			RUN = nullptr;
			STATE = 0;
			return;
		}
		if (SchedPtr->IO_requesthandling(RUN))
		{
			RUN = nullptr;
			STATE = 0;
			return;
		}
	}
	if (RUN)
		RUN->incrementCountsteps(1);
}

void EDF::addToMyRdy(PROCESS* process)
{
	RDY.enqueue(process, process->get_deadline());
	ExpectedFinishTime += process->get_CT() - process->get_countsteps();
	process->setlastCT(process->get_CT() - process->get_countsteps());
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
			ExpectedFinishTime -= toberun->getlastCT();
			return true;
		}
	}
	return false;
}

PROCESS* EDF::removeTopOfMyRDY()
{
	PROCESS* top = nullptr;
	if (RDY.dequeue(top)) {
		ExpectedFinishTime -= top->getlastCT();
		RSIZE--;
	}
	return top;
}

void  EDF::PrintMyReady()
{
	RDY.printContents();
}



