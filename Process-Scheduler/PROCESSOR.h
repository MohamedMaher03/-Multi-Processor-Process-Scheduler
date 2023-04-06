#pragma once
#include"QueueADT.h"
#include"PROCESS.h"
#include<string>
class PROCESSOR
{
public:

	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual int getRSIZE() = 0; //get the RDY Queue size 
	virtual string gettype() = 0;//get type of processor

};

