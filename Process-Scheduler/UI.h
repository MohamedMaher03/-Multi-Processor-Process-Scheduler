#pragma once
#include "PROCESS.h"
#include "PROCESSOR.h"
#include "LinkedQueue.h"
#include "LinkedPriorityQueue.h"
#include <string>
class PROCESSOR;
class UI
{
	enum MODE;
public:
	void printInteractive(int Time, PROCESSOR**, int ProcessorsCount, LinkedQueue<PROCESS*>, int, PROCESS**, int, LinkedPriorityQueue<PROCESS*>, int, int,int );
	void printStepByStep(int Time, PROCESSOR**, int ProcessorsCount, LinkedQueue<PROCESS*>, int, PROCESS**, int, LinkedPriorityQueue<PROCESS*>, int, int);
	void printSilent();
	void PrintProcessorReadies(PROCESSOR*); //Prints either RDY queue of processors
	void PrintQueue(LinkedQueue<PROCESS*> Q);
	void PrintRunning(PROCESS**, int, int, PROCESSOR**); //Prints Running processes
	string ReadFileName();
	void PrintMessage(string);
	int SelectRunMode();
};

