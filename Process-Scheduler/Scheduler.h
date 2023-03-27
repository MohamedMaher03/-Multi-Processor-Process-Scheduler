#pragma once
#include "LinkedQueue.h"
#include "PROCESS.h"
#include "PROCESSOR.h"
#include "UI.h"
class Scheduler
{
	int TIMESTEP;
	PROCESSOR** ListOfProcessors;
	int totalProcessors;
	//These 3 queues are common across all processes
	LinkedQueue<PROCESS*> NEW;
	LinkedQueue<PROCESS*> BLK;
	LinkedQueue<PROCESS*> TRM;
	UI* UIptr;

public:
	void LoadData(); // open the input file and load all processes into NEW list

	void SaveData(); // produce the output file at end of simulation

	void Print(); 

};

