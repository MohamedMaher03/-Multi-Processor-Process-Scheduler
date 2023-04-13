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
	bool PromoteProcess();
	void KillRandomly(int index); //Iterate over your RDY list and kill the process with given index
};

