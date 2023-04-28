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

FCFS::~FCFS()
{
}

void FCFS::ScheduleAlgo()
{
}

void FCFS::ScheduleAlgo()
{


	while (!RDY.IsEmpty()) 
	{
		if (!RUN)
		{
			RUN = RDY.peek();
			RDY.DeleteFirst();
			RUN->set_starttime(SchedPtr->get_TIMESTEP());
			STATE = 1;
		}
 
		if (RUN->get_CT() <= RUN->get_countsteps())
			
		{
					SchedPtr->Add_toterminatedlist(RUN);
					RUN = nullptr;
					STATE = 0;
		}
	
	}
	// lesa lazem a check al incrementation of the time step emta
}


void FCFS::addToMyRdy(PROCESS *P)
{ 
	RDY.InsertEnd(P);
	ExpectedFinishTime += P->get_CT();
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
		TEMP = RDY.peek()->getItem();
		if (x == TEMP->get_AT())
			return false;
		RUN = TEMP;
		STATE = 1;
		RDY.DeleteFirst();
		RSIZE--;
		return true;
	}
	return false;
}

PROCESS* FCFS::KillRandomly(int index)
{
	/*if (RUN)
	{
		if (index == RUN->get_PID())
		{
			PROCESS* temp = RUN;
			SchedPtr->Add_toterminatedlist(temp);
			STATE = 0;
			RUN = nullptr;
			return;
		}
	}*/
	if (RDY.IsEmpty())
		return nullptr;
	PROCESS* temp = new PROCESS(0, 0, 0, 0);
	RDY.KILL(index, temp);
	if (temp)
		RSIZE--;
	return temp;
}
