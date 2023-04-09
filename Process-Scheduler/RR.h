#include "PROCESSOR.h"
#include"PROCESS.h"
#include"LinkedQueue.h"
#include"Scheduler.h"

class RR : public PROCESSOR
{
	LinkedQueue<PROCESS*>RDY;

	
	Scheduler* sch_ptr;
	
public:
	RR();
	virtual void ScheduleAlgo();//function moving process from RDY to RUN differ for each processor type

};

