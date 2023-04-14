#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
class PROCESSOR;
class SJF : public PROCESSOR
{
private:
	bool STATE;
	LinkedPriorityQueue<PROCESS*>RDY;
	PROCESS* RUN;
public:
	SJF();
	void ScheduleAlgo();
	bool PromoteProcess(int x);
	void addToMyRdy(PROCESS*process);  //Schedular class will set RDYLIST
	void PrintMyReady();
};

