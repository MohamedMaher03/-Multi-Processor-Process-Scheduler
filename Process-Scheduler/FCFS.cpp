#include "FCFS.h"
#include "Scheduler.h"
using namespace std;

FCFS::FCFS(Scheduler* sc):PROCESSOR(sc)
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


	while (!RDY.IsEmpty()) 
	{
		if (!RUN)
		{
			RUN = RDY.peek()->getItem();
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
void FCFS::Killchildren(PROCESS* P)
{
	if (P->getChild1()) {
		SchedPtr->Add_toterminatedlist(P->getChild1());
	}
	if (P->getChild2()) {
		SchedPtr->Add_toterminatedlist(P->getChild2());
	}
	P->setChild1(nullptr);
	P->setChild2(nullptr);
	//or if it has children i can search in all fcfs prosessor for them and delete their node
}

bool FCFS::Killsignal(int time, int id)
{
	if (time != SchedPtr->get_TIMESTEP())
	{
		return false;
	}
	if (RUN->get_PID() == id)
	{
		SchedPtr->Add_toterminatedlist(RUN);
		if (RUN->getChild1() || RUN->getChild2()) //if prcocess have child and process terminate then their children must also terminated
		{
			Killchildren(RUN);
		}
		RUN = nullptr;
		STATE = 0;
		return true;
	}
	for (int i = 0;i < RSIZE;i++) {
		Node<PROCESS*>* current = RDY.peek();
			if (current->getItem()->get_PID() == id) 
			{
				PROCESS* itemPtr = current->getItem();
				RDY.DeleteNode(itemPtr);
				SchedPtr->Add_toterminatedlist(itemPtr);
				RSIZE--;
				if (itemPtr->getChild1() || itemPtr->getChild2())
				{
					Killchildren(itemPtr);
				}
				return true;
			}
			current = current->getNext();
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
