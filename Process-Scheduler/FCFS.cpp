#include "FCFS.h"
#include "Scheduler.h"
#include<random>
using namespace std;
LinkedQueue<Pair*> FCFS::ToBeKilled;

FCFS::FCFS(Scheduler* sc):PROCESSOR(sc)
{  
	STATE = false;
	RUN = nullptr;
	TYPE = "FCFS";
	RSIZE = 0;
	PLoad = 0;
	PUtil = 0;
	TotalBusyTime = 0;
}

FCFS::~FCFS()
{
}


void FCFS::ScheduleAlgo()
{
	if (!RUN)
		TotalIdleTime++;
	else
		TotalBusyTime++;

	if (!RUN && RDY.IsEmpty())
		return;
	Pair* target;
	if (!ToBeKilled.isEmpty())
	{
		ToBeKilled.peek(target);
		KillSignal(target->getfirst(), target->getsecond());
	}
	if (!RUN && !RDY.IsEmpty())
	{
			PROCESS* TEMP;
			TEMP = RDY.peek()->getItem();
			RUN = TEMP;
			STATE = 1;
			RUN->set_starttime(SchedPtr->get_TIMESTEP());
			RDY.DeleteFirst();
			RSIZE--;
			ExpectedFinishTime -= RUN->get_CT();
			RUN->incrementCountsteps(1);
	}
 
	else{
		if(SchedPtr->Process_completion(RUN))
		{
			//SchedPtr->Add_toterminatedlist(RUN);
			RUN = nullptr;
			STATE = 0;
			return;
		}
		else if (SchedPtr->IO_requesthandling(RUN))
		{
			RUN = nullptr;
			STATE = 0;
			return;
		}
		else
		{
			RUN->incrementCountsteps(1);
		}
	}
	if (RUN)
		RUN->incrementCountsteps(1);
	
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

bool FCFS::PromoteProcess()
{
	if (!STATE && !RDY.IsEmpty())
	{	 
		PROCESS* TEMP;
		TEMP = RDY.peek()->getItem();
		RUN = TEMP;
		STATE = 1;
		RDY.DeleteFirst();
		ExpectedFinishTime -= TEMP->get_CT();
		RSIZE--;
		return true;
	}
	return false;
}
void FCFS::Killchildren(PROCESS* P)
{
	if (!P->getChild1() && !P->getChild2())
	{
		Kill(P);
		return;
	}
	if (P->getChild1())
	Killchildren(P->getChild1());
	if(P->getChild2())
	Killchildren(P->getChild2());
	Kill(P);

}
bool FCFS::isInMyRdy(PROCESS* target)
{
	if (RDY.Find(target))
	{
		RDY.DeleteNode(target);
		ExpectedFinishTime -= target->get_CT();
		RSIZE--;
		return true;
	}
	return false;
}
void FCFS::addToBeKilled(Pair* tmp)
{
	ToBeKilled.enqueue(tmp);
}
void FCFS::ForkTree(PROCESS* P)
{ 
	if (STATE)
	{
		if (RUN->get_PID() == P->get_PID())
		{
			 SchedPtr->increment_LiveTotalProcesses();
			 int Remaining_CT = P->get_CT() - P->get_countsteps();
			 PROCESS* C = new PROCESS(SchedPtr->get_TIMESTEP(), SchedPtr->get_LiveTotalProcesses(), Remaining_CT, 0);
			 C->set_isforked();
			 P->set_isforked();
			 if (!P->getChild1())
			 {
				 P->setChild1(C);
			 }
			 else
				 P->setChild2(C);
			
			 addToMyRdy(C);
		}
	}
}

void FCFS::RemoveFromMyRdy(PROCESS* target)
{
	RDY.DeleteNode(target);
}

int FCFS::random()
{
	random_device rd;
	mt19937 gen(rd());

	// Define the distribution for the random number
	uniform_int_distribution<> dis(1, 100);

	// Generate and return the random number
	return dis(gen);
}

void FCFS::Kill(PROCESS* target)
{
	target->set_IsKilled();
	SchedPtr->Add_toterminatedlist(target);
	SchedPtr->RemoveFromEverywhere(target);
	SchedPtr->increment_KilledCount();
}

bool FCFS::KillSignal(int id, int time)
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
				ExpectedFinishTime -= itemPtr->get_CT();
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

PROCESS* FCFS::removeTopOfMyRDY()
{
	PROCESS* top = nullptr;
	top=RDY.peek()->getItem();
	if (top) 
	{
		RDY.DeleteFirst();
		RSIZE--;
		ExpectedFinishTime -= top->get_CT();
	}
	return top;
}

