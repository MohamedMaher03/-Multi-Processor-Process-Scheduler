#include "UI.h"
#include<iostream>
using namespace std;
void UI::printInteractive(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, PROCESS** RUN, int RunningCountIndex, LinkedQueue<PROCESS*> TRM, int TSize, int RunningCount)
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
	cout << "------------ - BLK processes  ------------ - " << endl;
	cout << BSize << " BLK: "; PrintQueue(BLK); cout << endl;
	cout << "\n------------ - RUN processes  ------------ - " << endl;
	cout << RunningCount << " RUN: "; PrintRunning(RUN, RunningCountIndex, ProcessorsCount); cout << endl;
	cout << "\n------------ - TRM processes  ------------ - " << endl;
	cout << TSize << " TRM: "; PrintQueue(TRM); cout << endl;
	cout << "\n";
	cout << "PRESS ENTER E TO MOVE TO NEXT STEP !" << endl;
	cout << "\n \n";
	/*while (1)
	{
		char x;
		cin >> x;
		if (x == 'E' || x == 'e')
			break;
	}*/
}
void UI::printStepByStep(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, PROCESS** RUN, int RunningCountIndex, LinkedQueue<PROCESS*> TRM, int TSize, int RunningCount)
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
	cout << RunningCount << " RUN: "; PrintRunning(RUN, RunningCountIndex, ProcessorsCount);
	cout << "\n------------ - TRM processes------------ - " << endl;
	cout << TSize << " TRM: "; PrintQueue(TRM);
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl;
}
void UI::printSilent()
{
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
	Q.printContents();
}

void UI::PrintRunning(PROCESS** Run, int Size, int TotalCPUs)
{
	if (Size > TotalCPUs)
		Size = TotalCPUs;
	for (int i = 0; i < Size; i++)
	{
		if(Run[i])
		cout << Run[i]->get_PID() << ", ";
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
