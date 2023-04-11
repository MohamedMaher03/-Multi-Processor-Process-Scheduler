#pragma once
#include "PROCESSOR.h"
#include "LinkedList.h"

class FCFS :public PROCESSOR
{
private:
	LinkedList <PROCESS*> RDY;
	PROCESS* RUN;

public: 
	FCFS(); //FCFS class has default constructor
	void ScheduleAlgo();
	void addToMyRdy(PROCESS *P);
	void PrintMyReady();
	void PromoteProcess();
};

