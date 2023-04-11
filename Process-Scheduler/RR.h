#include "PROCESSOR.h"
#include"PROCESS.h"
#include"LinkedQueue.h"
#include"Scheduler.h"

class RR : public PROCESSOR
{
	LinkedQueue<PROCESS*>RDY;

public:
	RR();
	virtual void ScheduleAlgo();//function moving process from RDY to RUN differ for each processor type
	virtual void PrintMyReady();
	virtual void addToMyRdy(PROCESS*);
	virtual void PromoteProcess(); //Makes the process AS running, and removes it from RDY queue

};
