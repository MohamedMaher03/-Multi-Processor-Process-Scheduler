#pragma once
#include "PROCESSOR.h"
#include "LinkedList.h"

class FCFS :public PROCESSOR
{
private:
	LinkedList <PROCESS*> RDY;
	
public: 
	FCFS(Scheduler*); //FCFS class has default constructor
	~FCFS();
	void ScheduleAlgo();
	void addToMyRdy(PROCESS *P);
	void PrintMyReady();
	bool PromoteProcess(int);
	PROCESS* KillRandomly(int index); //Iterate over your RDY list and kill the process with given index
};

