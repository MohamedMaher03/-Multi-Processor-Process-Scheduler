#include "PROCESSOR.h"
#include"PROCESS.h"
#include"LinkedQueue.h"
#include"Scheduler.h"

class RR : public PROCESSOR
{
	LinkedQueue<PROCESS*>RDY;

	PROCESS* RUN ;
	Scheduler* sch_ptr;
	string type;
public:
	RR();
	virtual void ScheduleAlgo();//function moving process from RDY to RUN differ for each processor type
	
	virtual int getRSIZE(); //get the RDY Queue size 
	virtual string gettype();//get type of processor

};

