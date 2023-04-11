#include "SJF.h"
using namespace std;
SJF::SJF()
{
	RUN = nullptr;
	TYPE = "SJF";
}

void SJF::ScheduleAlgo()
{
	/*
	while (!RDY.isEmpty()) {
		if (!STATE)  //if the processor is IDLE 
		{
			PROCESS* HighestPriorityPROCESS;
			if (RDY.dequeue(HighestPriorityPROCESS)) {
				RUN = HighestPriorityPROCESS;
				RUN->set_starttime(schedulerptr->get_TIMESTEP());  //set start time if process didn't start CPU before 
				STATE = 1;
			}
		}
		   // if there is a process running in the CPU
		
			if (RUN->get_countsteps() > RUN->get_CT())
			{
				schedulerptr->Add_toterminatedlist(RUN);
				RUN = nullptr;
				STATE = 0;
			}
			else if (RUN->get_N()>0 && RUN->get_countN()<=RUN->get_N())
			{
				if (RUN->get_countsteps() == RUN->get_IO_R(RUN->get_countN()))
				{
					RUN->incrementCountsteps(1);
					RUN->incrementcountN();
					schedulerptr->Add_toblocklist(RUN);
					RUN = nullptr;
					STATE = 0;
				}
				else {
					RUN->incrementCountsteps(1);
				}
			}
			else {
				RUN->incrementCountsteps(1);
			}
	}
	*/
}

void SJF::addToMyRdy(PROCESS* process)
{
	RDY.enqueue(process);
}

bool SJF::PromoteProcess()
{
	if (!STATE)// the processor is IDLE
	{
		PROCESS* toberun;
		if (RDY.dequeue(toberun))
		{
			RUN = toberun;
			SchedPtr->AddToRunning(toberun); //Add process to queue of running processes in scheduler
			return true;
		}

	}
	return false;
}

void  SJF::PrintMyReady() {
	RDY.printContents();
}

