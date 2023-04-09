#pragma once
#include"LinkedQueue.h"
#include "PROCESS.h"
class PROCESSOR
{
protected:
	LinkedQueue<PROCESS*> RDY;
	PROCESS* RUN;
	string TYPE;
	int RSIZE;
	bool STATE; // 0->IDLE |_||_| 1->BUSY
	int ProcessorLoad;
	int ProcessorUtilization;
public:
	PROCESSOR(string type);
	~PROCESSOR();
	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual void PrintMyReady() = 0;
	virtual void addToMyRdy(PROCESS*) = 0;
	int getRSIZE(); //get the RDY Queue size 
	string getType(); //get type of processor
	PROCESS* getCurrentlyRunning(); //returns address of currently running process for each processor, null otherwise
	bool getState();
	virtual void PromoteProcess() = 0; //Makes the process AS running, and removes it from RDY queue

};

