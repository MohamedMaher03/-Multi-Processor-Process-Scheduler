#pragma once
#include "PROCESS.h"
#include "PROCESSOR.h"
#include "LinkedQueue.h"
class UI
{
	enum MODE;
public:
	void printInteractive(int Time, PROCESSOR**, int ProcessorsCount, LinkedQueue<PROCESS*>, int, LinkedQueue<PROCESS*>, int, LinkedQueue<PROCESS*>, int);
	void printStepByStep(int Time, PROCESSOR**, int ProcessorsCount, LinkedQueue<PROCESS*>, int, LinkedQueue<PROCESS*>, int, LinkedQueue<PROCESS*>, int);
	void printSilent();
	void PrintQueue(PROCESSOR*);
	void PrintQueue(LinkedQueue<PROCESS*> Q);
	

};

