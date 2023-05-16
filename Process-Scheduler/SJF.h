#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
#include "Scheduler.h"
class SJF : public PROCESSOR
{
private:
	LinkedPriorityQueue<PROCESS*>RDY;
public:
	SJF(Scheduler* scheduler);
	void ScheduleAlgo() override;
	bool PromoteProcess();
	PROCESS* removeTopOfMyRDY() override;
	void addToMyRdy(PROCESS*process);  //Schedular class will set RDYLIST
	void PrintMyReady() override;
	PROCESS* find_first_nonforked_elemnt();
};

