#pragma once
#include "PROCESSOR.h"
#include "LinkedPriorityQueue.h"
#include "Scheduler.h"
class EDF : public PROCESSOR
{
private:
	LinkedPriorityQueue<PROCESS*>RDY;
public:
	EDF(Scheduler* scheduler);
	void ScheduleAlgo() override;
	bool PromoteProcess();
	PROCESS* removeTopOfMyRDY() override;
	void addToMyRdy(PROCESS* process);  //Schedular class will set RDYLIST
	void PrintMyReady() override;
};

