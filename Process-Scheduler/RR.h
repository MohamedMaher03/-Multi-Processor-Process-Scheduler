#pragma once
#include "PROCESSOR.h"
#include"LinkedQueue.h"

class PROCESSOR;

class RR : public PROCESSOR
{
	LinkedQueue<PROCESS*>RDY;
	bool STATE;
	PROCESS* RUN;

public:
	RR();
	void ScheduleAlgo();//function moving process from RDY to RUN differ for each processor type
	void PrintMyReady();
	void addToMyRdy(PROCESS*);
	bool PromoteProcess(int); //Makes the process AS running, and removes it from RDY queue

};
