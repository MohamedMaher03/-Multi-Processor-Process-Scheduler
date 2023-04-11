#include "FCFS.h"
using namespace std;

FCFS::FCFS()
{  
	RUN = nullptr;
    TYPE = "FCFS";
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
}

void FCFS::PrintMyReady()
{
    RDY.PrintList();
}

bool FCFS::PromoteProcess()
{
    if (!STATE && !RDY.IsEmpty())
    {
         
        PROCESS* TEMP;
        TEMP = RDY.get_Head()->getItem();
        RUN = TEMP;
        STATE = 1;
        SchedPtr->AddToRunning(TEMP); //Add process to queue of running processes in scheduler
        return true;
    }
    return false;
}
