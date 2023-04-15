#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
class PROCESSOR;
class SJF : public PROCESSOR
{
private:
	LinkedPriorityQueue<PROCESS*>RDY;
public:
	SJF();
	void ScheduleAlgo();
	bool PromoteProcess(int x);
	void addToMyRdy(PROCESS*process);  //Schedular class will set RDYLIST
	void PrintMyReady();
};

