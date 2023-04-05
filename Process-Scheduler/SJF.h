#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
#include "PROCESS.h"
class SJF : public PROCESSOR
{
private:
	LinkedPriorityQueue<PROCESS*>RDY;
	PROCESS*RUN;
	Scheduler*schedulerptr;
	int RSIZE;
	string type;
public:
	SJF();
	void ScheduleAlgo();
	void Set_RDYLIST(PROCESS*process);  //Schedular class will set RDYLIST
	int get_RSIZE();
};

