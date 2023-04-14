#include "FCFS.h"
#include "Scheduler.h"
using namespace std;

FCFS::FCFS()
{  
	STATE = false;
	RUN = nullptr;
	TYPE = "FCFS";
	RSIZE = 0;
}

void FCFS::ScheduleAlgo()
{
}

/*void FCFS::ScheduleAlgo()
{


	while (!RDY.IsEmpty()) 
	{
		if (!RUN)
		{
			RUN = RDY.get_Head();
			RDY.DeleteFirst();
			RUN->set_starttime(SCH_ptr->get_TIMESTEP());
			


		}
	}
}*/


void FCFS::addToMyRdy(PROCESS *P)
{ 
	RDY.InsertEnd(P);
	RSIZE++;
}

void FCFS::PrintMyReady()
{
	RDY.PrintList();
}

bool FCFS::PromoteProcess(int x)
{
	if (!STATE && !RDY.IsEmpty())
	{	 
		PROCESS* TEMP;
		TEMP = RDY.get_Head()->getItem();
		if (x == TEMP->get_AT())
			return false;
		RUN = TEMP;
		STATE = 1;
		RDY.DeleteFirst();
		return true;
	}
	return false;
}

void FCFS::KillRandomly(int index)
{
}
