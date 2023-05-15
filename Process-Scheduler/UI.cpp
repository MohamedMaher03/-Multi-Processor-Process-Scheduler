#include "UI.h"
#include <chrono>  // for chrono::seconds
#include <thread>  // for this_thread::sleep_for
#include<iostream>
using namespace std;
void UI::printInteractive(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, int* RUN, LinkedQueue<PROCESS*> TRM, int TSize, int RunningCount)
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
	cout << RunningCount << " RUN: "; PrintRunning(RUN, ProcessorsCount); cout << endl;
	cout << "\n------------ - TRM processes  ------------ - " << endl;
	cout << TSize << " TRM: "; TRM.printContents(); cout << endl;
	cout << "\n";
	cout << "PRESS ENTER E TO MOVE TO NEXT STEP !" << endl;
	cout << "\n \n";
	
	/*while (1)
	{
		char x;
		cin >> x;
		if (x == 'e' || x == 'E')
			break;
	}*/
	
}
void UI::printStepByStep(int Time, PROCESSOR** ProccessorList, int ProcessorsCount, LinkedQueue<PROCESS*> BLK, int BSize, int* RUN, LinkedQueue<PROCESS*> TRM, int TSize, int RunningCount)
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
	cout << RunningCount << " RUN: "; PrintRunning(RUN, ProcessorsCount);
	cout << "\n------------ - TRM processes------------ - " << endl;
	cout << TSize << " TRM: "; TRM.printContents();
	cout << "\n *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	this_thread::sleep_for(chrono::seconds(1)); // waits for one second
}
void UI::printSilent()
{
	cout << "Silent Mode.........." << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Simulation Starts..." << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Simulation ends, Output file created" << endl;
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

void UI::PrintRunning(int* Run, int s)
{
	for (int i = 0; i < s; i++)
	{
		if (Run[i])
			cout << Run[i] << "(P" << i + 1 << "), ";
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

int UI::SelectRunMode()
{
	cout << "-------  PLEASE CHOOSE THE RUNNING MOOD: ---------- \n\n";
	cout << "I for Interactive Mood" << endl;
	cout << "B for Step-By-Step Mood" << endl;
	cout << "S for Silent Mood" << endl;
	char x;
	cin >> x;
	if (x == 'I' || x == 'i')
		return 1;
	else if (x == 'B' || x == 'b')
		return 2;
	else if (x == 'S' || x == 's')
		return 3;
	return 0;
}
