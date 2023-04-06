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
	virtual void ScheduleAlgo() = 0;
	void PrintMyReady();
	void addToMyRdy(PROCESS*);
	int getRSIZE();
};

