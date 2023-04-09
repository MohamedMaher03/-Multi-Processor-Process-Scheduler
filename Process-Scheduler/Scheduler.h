#pragma once
#include "LinkedQueue.h"
#include "PROCESS.h"
#include "PROCESSOR.h"
#include "UI.h"
#include "PROCESS.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
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
	int FCFS_Count;
	int SJF_Count;
	int RR_Count;
	int TimeSlice;
	int RTF;
	int MaxW;
	int STL;
	int Forkability;
	int ProcessesCount;
	LinkedQueue<int>ProcessesToBeKilled;
	LinkedQueue<int>TimeOfDeath;
	int BLK_Count;
	int RUN_Count;
	int TRM_Count;
	int RunningCount; // Total number of currently running processes
	int* Running; //This is an arry containg IDs of Running processes from each processor
	//--------- STATISTICS -------------
	int AvgWaitingTime; //Average waiting time for all processes
	int AvgResponseTime; //Average Response time for all processes
	int AvgTRT; //Average Turnaround time for all processes
	int MigPercent; //Percentage of process migration due to RTF and MaxW
	int StealPercent; //Percentages of processes moved by works steal
	int ForkPercent; //Percentage of process fork
	int KillPercent; //Percentage of process kill
	int AvgUtilization; //Average utilization for all processors

public:
	void LoadData(); // open the input file and load all processes into NEW list
	void SaveData(); // produce the output file at end of simulation
	void CreateProcessors(int, int, int);
	void Print(char); //Decides which mode ([I]nteractive - [S]ilent - Step[B]yStep) 
	void Add_toblocklist(PROCESS*blockedprocess);
	void Add_toterminatedlist(PROCESS* terminatedprocess);
	int get_TIMESTEP();
	int getTimeSlice();
	int getRTF();
	Scheduler();
	void UpdateRunningProcesses(); //Iterates over all processors and adds Currently Running Processes
	void SIMULATE();
	void CheckNewArrivals(int& count, int& new_curindx); //Checks the NEW queue for processes arriving at current Timestep and add them to RDY
	bool PromoteRdyToRun(); //This function promotes a process from RDY queue to Running if processor is IDLE
	int Randomizer(); //Generates Random numbers from 1 to 100
	void AllocatingProcesses(); //Use the radnomizer to distribute processes ranadomly
	bool AllDone(); //All is done if RDY queues of all processors are all empty
	~Scheduler();
};

