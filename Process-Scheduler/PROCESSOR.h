#pragma once
#include"LinkedQueue.h"
#include "PROCESS.h"
class PROCESSOR
{
	LinkedQueue<PROCESS*> RDY;
	PROCESS* RUN;
	string TYPE;
	int RSIZE;
	bool STATE; // 0->IDLE |_||_| 1->BUSY
public:
	PROCESSOR(string type);
	~PROCESSOR();
	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual void PrintMyReady();
	void addToMyRdy(PROCESS*);
	int getRSIZE(); //get the RDY Queue size 
	string getType(); //get type of processor
	PROCESS* getCurrentlyRunning(); //returns address of currently running process for each processor
	bool getState();

};

