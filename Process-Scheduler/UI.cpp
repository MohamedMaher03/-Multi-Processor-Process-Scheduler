#include "UI.h"
#include<iostream>
using namespace std;
void UI::printInteractive(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, int* RUN, int RSize, LinkedQueue<PROCESS*> TRM, int TSize)
{
	cout << "Current Timestep:" << Time << "\n"
		"-------------  RDY processes  -------------" << endl;
	for (int i = 0; i < ProcessorsCount; i++)
	{
		cout << "processor " << i + 1 << " [" << ProccessorList[i]->getType() << "]: " <<
			ProccessorList[i]->getRSIZE() << " RDY: ";
		/*
		- Each processor must have RSIZE (a count for the ready queue current size)
		- Each processor must have type string that is one of those (FCFS / SJF / RR)
		- Each processor must have RDY queue 
		*/
		ProccessorList[i]->PrintMyReady();
		cout << endl;
	}
	cout << "------------ - BLK processes------------ - " << endl;
	cout << BSize << " BLK: "; PrintQueue(BLK);
	cout << "\n------------ - RUN processes------------ - " << endl;
	cout << RSize << " RUN: "; PrintRunning(RUN, RSize);
	cout << "\n------------ - TRM processes------------ - " << endl;
	cout << TSize << " TRM: "; PrintQueue(TRM);
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
}
void UI::printStepByStep(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, int* RUN, int RSize, LinkedQueue<PROCESS*> TRM, int TSize)
{
	cout << "Current Timestep:" << Time << "\n"
		"-------------  RDY processes  -------------" << endl;
	for (int i = 0; i < ProcessorsCount; i++)
	{
		cout << "processor " << i + 1 << " [" << ProccessorList[i]->getType() << "]: " <<
			ProccessorList[i]->getRSIZE() << " RDY: ";
		/*
		- Each processor must have RSIZE (a count for the ready queue current size)
		- Each processor must have type string that is one of those (FCFS / SJF / RR)
		- Each processor must have RDY queue
		*/
		ProccessorList[i]->PrintMyReady();
		cout << endl;
	}
	cout << "------------ - BLK processes------------ - " << endl;
	cout << BSize << " BLK: "; PrintQueue(BLK);
	cout << "\n------------ - RUN processes------------ - " << endl;
	cout << RSize << " RUN: "; PrintRunning(RUN, RSize);
	cout << "\n------------ - TRM processes------------ - " << endl;
	cout << TSize << " TRM: "; PrintQueue(TRM);
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
}
enum UI::MODE
{
	INTERACTIVE,
	StepByStep,
	Silent
};
void UI::PrintProcessorReadies(PROCESSOR* K)
{
	K->PrintMyReady();
	return;

}

void UI::PrintQueue(LinkedQueue<PROCESS*> Q)
{
	LinkedQueue<PROCESS*> Q2 = Q;
	PROCESS* tmp;
	while (!Q.isEmpty())
	{
		Q.dequeue(tmp);
		cout << tmp->get_PID() << " ,";
		Q2.enqueue(tmp);
	}
	cout << endl;
	Q = Q2;
}

void UI::PrintRunning(int* Run, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		cout << Run[i] << ", ";
	}
}

string UI::ReadFileName()
{
	cout << "Please Enter the filename to load data from: " << endl;
	string userChosenName;
	cin >> userChosenName;
	userChosenName = userChosenName + ".txt";
	return userChosenName;
}
void UI::PrintMessage(string x)
{
	cout << x;
}
