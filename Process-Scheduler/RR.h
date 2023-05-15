#pragma once
#include "PROCESSOR.h"
#include"LinkedQueue.h"

class PROCESSOR;

class RR : public PROCESSOR
{
	LinkedQueue<PROCESS*>RDY;

public:
	RR(Scheduler* scheduler);
	~RR();
	void ScheduleAlgo() override;//function moving process from RDY to RUN differ for each processor type
	void PrintMyReady() override;
	void addToMyRdy(PROCESS*) override;
	PROCESS* removeTopOfMyRDY() override;
	bool PromoteProcess(); //Makes the process AS running, and removes it from RDY queue

};
