#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
#include "Scheduler.h"
#include "PROCESS.h"
class SJF : public PROCESSOR
{
private:
	LinkedPriorityQueue<PROCESS*>RDY;
public:
	SJF();
	void ScheduleAlgo();
	void PromoteProcess();
	void addToMyRdy(PROCESS*process);  //Schedular class will set RDYLIST
	void PrintMyReady();
};

