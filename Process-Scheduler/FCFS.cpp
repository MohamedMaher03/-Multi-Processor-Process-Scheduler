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
	CooldownTimer = 0;
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

	if (SchedPtr->random() <= 1)
	{
		STOP(SchedPtr->getCoolTime());
		return;
	}

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
		ExpectedFinishTime -= RUN->getlastCT();
		SchedPtr->increment_runningcount();
		ForkTree(TEMP);
		if (TEMP->get_RT() == -1)
			TEMP->set_RT(SchedPtr->get_TIMESTEP() - TEMP->get_AT());
	}
 
	if (SchedPtr->Process_completion(RUN))
	{
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

	if (RUN)
		if (SchedPtr->MIG_FCFS_RR(RUN))
		{
			SchedPtr->RemoveFromRunning(RUN);
			RUN = nullptr;
			SchedPtr->decrement_runningcount();
					
		}
		else
			RUN->incrementCountsteps(1);
	
}


void FCFS::addToMyRdy(PROCESS *P)
{ 
	RDY.InsertEnd(P);
	ExpectedFinishTime += P->get_CT() - P->get_countsteps();
	P->setlastCT(P->get_CT() - P->get_countsteps());
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
		ExpectedFinishTime -= TEMP->getlastCT();
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
		ExpectedFinishTime -= target->getlastCT();
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
	if (P->getChild1() && P->getChild2())
		return;
	int x = SchedPtr->random();
	if (x <= SchedPtr->get_ForkPercent())
	{
		SchedPtr->CreateNewProcess(P);	 
	}
}

void FCFS::RemoveFromMyRdy(PROCESS* target)
{
	RDY.DeleteNode(target);
}

PROCESS* FCFS::find_first_nonforked_elemnt()
{
	if (RDY.IsEmpty())
		return nullptr;
	PROCESS* firstnonforkedelement = nullptr;
	bool find = false;
	LinkedList<PROCESS*>TEMP;
	while (!RDY.IsEmpty()) 
	{
		PROCESS* top;
		top = RDY.peek()->getItem();
		TEMP.InsertEnd(top);
		RDY.DeleteFirst();
		if (!(top->get_isforked()) && !find) {
			firstnonforkedelement = top;
			find = true;
		}
	}
	while (!TEMP.IsEmpty()) 
	{
		PROCESS* top;
		top = TEMP.peek()->getItem();
		RDY.InsertBeg(top);
		TEMP.DeleteFirst();
	}
	return firstnonforkedelement;

}

void FCFS::Kill(PROCESS* target)
{
	target->set_IsKilled();
	SchedPtr->Add_toterminatedlist(target);
	SchedPtr->RemoveFromEverywhere(target);
	SchedPtr->increment_KilledCount();
	Pair* x;
	ToBeKilled.dequeue(x);
}

void FCFS::KillSignal(int time, int id)
{
	if (time != SchedPtr->get_TIMESTEP() || !RUN)
	{
		return;
	}
	if (RUN->get_PID() == id)
	{
		if (RUN->getChild1() || RUN->getChild2()) //if prcocess have child and process terminate then their children must also terminated
		{
			Killchildren(RUN);
		}
		else
			Kill(RUN);
		RUN = nullptr;
		STATE = 0;
		return;
	}
	PROCESS* temp = nullptr;
	LinkedList<PROCESS*>TMP;
	while (!RDY.IsEmpty()) 
	{
		PROCESS* top;
		top = RDY.peek()->getItem();
		RDY.DeleteFirst();
		if (top->get_PID() == id) 
		{
			if (top->getChild1() || top->getChild2()) //if prcocess have child and process terminate then their children must also terminated
			{
				Killchildren(top);
			}
			else
				Kill(top);
			RSIZE--;
		}
		else
			TMP.InsertEnd(top);
	}
	while (!TMP.IsEmpty()) 
	{
		PROCESS* top;
		top = TMP.peek()->getItem();
		RDY.InsertEnd(top);
		TMP.DeleteFirst();
	}
	return;
}

PROCESS* FCFS::removeTopOfMyRDY()
{
	PROCESS* top;
	top=RDY.peek()->getItem();
	if (top) 
	{
		RDY.DeleteFirst();
		RSIZE--;
		ExpectedFinishTime -= top->getlastCT();
	}
	return top;
}

void FCFS::STOP(const int x)
{
	CooldownTimer = x;
	if (RUN)
	{
		SchedPtr->FindShortestProcessor()->addToMyRdy(RUN);
		SchedPtr->decrement_runningcount();
		RUN = NULL;
	}
	while (!RDY.IsEmpty())
	{
		PROCESS* temp;
		temp=RDY.peek()->getItem();
		RDY.DeleteFirst();
		SchedPtr->FindShortestProcessor()->addToMyRdy(temp);
		RSIZE--;
	}
	ExpectedFinishTime = 0;
}

