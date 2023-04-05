#include "SJF.h"
#include "Scheduler.h"

SJF::SJF()
{
	RUN = nullptr;
	type = "SJF";
}

void SJF::ScheduleAlgo()
{
	while (!RDY.isEmpty()) {
		if (!RUN)  //if the processor is IDLE 
		{
			PROCESS* HighestPriorityPROCESS;
			if (RDY.dequeue(HighestPriorityPROCESS)) {
				RUN = HighestPriorityPROCESS;
				RUN->set_starttime(schedulerptr->get_TIMESTEP());  //set start time if process didn't start CPU before 
			}
		}
		   // if there is a process running in the CPU
		
			if (RUN->get_countsteps() > RUN->get_CT())
			{
				schedulerptr->Add_toterminatedlist(RUN);
				RUN = nullptr;
			}
			else if (RUN->get_N()>0 && RUN->get_countN()<=RUN->get_N())
			{
				if (RUN->get_countsteps() == RUN->get_IO_R(RUN->get_countN()))
				{
					RUN->incrementCountsteps();
					RUN->incrementcountN();
					schedulerptr->Add_toblocklist(RUN);
					RUN = nullptr;
				}
				else {
					RUN->incrementCountsteps();
				}
			}
			else {
				RUN->incrementCountsteps();
			}
	}
}

void SJF::Set_RDYLIST(PROCESS* process)
{
	RDY.enqueue(process);
}

int SJF::get_RSIZE()
{
	return RDY.get_length();
}


