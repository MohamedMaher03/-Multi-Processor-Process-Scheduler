#pragma once
#include"LinkedQueue.h"
#include "PROCESS.h"
class PROCESSOR
{
	LinkedQueue<PROCESS*> RDY;
	PROCESS* RUN;
	string TYPE;
	int RSIZE;
public:
	PROCESSOR(string type);
	~PROCESSOR();
	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual void PrintMyReady() = 0;
	void addToMyRdy(PROCESS*);
	int getRSIZE(); //get the RDY Queue size 
	string getType(); //get type of processor

};

