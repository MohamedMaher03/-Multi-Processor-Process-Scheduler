#pragma once
<<<<<<< HEAD
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
=======
#include"QueueADT.h"
#include"PROCESS.h"
#include<string>
class PROCESSOR
{
public:

	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual int getRSIZE() = 0; //get the RDY Queue size 
	virtual string gettype() = 0;//get type of processor

>>>>>>> 7e20f2bfa29bed8de1551957d64895840a17dd5c
};

