#pragma once
#include "PROCESSOR.h"
#include "LinkedList.h"
#include "PROCESS.h"
#include "Scheduler.h"
class FCFS :public PROCESSOR
{
private:
	LinkedList <PROCESS*> RDY;
	PROCESS* RUN;
	Scheduler* SCH_ptr;

public: 
	FCFS(); //FCFS class has default constructor
	void ScheduleAlgo();
	void addToMyRdy(PROCESS *P);
	void PrintMyReady();
	void PromoteProcess();
};

