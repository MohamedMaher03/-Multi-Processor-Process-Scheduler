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
	PROCESSOR* ListOfProcessors [200];
	int totalProcessors;
	//These 3 queues are common across all processes
	LinkedQueue<PROCESS*> NEW;
	LinkedQueue<PROCESS*> BLK;
	LinkedQueue<PROCESS*> TRM;
	UI* UIptr;
	int RUNNING[200]; // An array of Running Processes' IDs. Index represents the number of processor (Index 0 => Processor 1)
	int FCFS_Count;
	int SJF_Count;
	int RR_Count;
	int TimeSlice;
	int RTF;
	int MaxW;
	int STL;
	int Forkability;
	int ProcessesCount;
	int BLK_Count;
	int TRM_Count;
	int RunningCount; // Total number of currently running processes
	int RunningCountIndex; //Inaccurate number of Running processes but useful for indexing the array
	int LiveTotalProcesses;
	LinkedList<PROCESS*> ForkedProcesses;
	string File;  // The name of the input file and will be used as the name of output file too
	//--------- STATISTICS -------------
	int AvgWaitingTime; //Average waiting time for all processes
	int AvgResponseTime; //Average Response time for all processes
	int AvgTRT; //Average Turnaround time for all processes
	int MigPercent_RTF; //Percentage of process migration due to RTF
	int MigPercent_MaxW; //Percentage of process migration due to MaxW
	int StealPercent; //Percentages of processes moved by works steal
	int ForkPercent; //Percentage of process fork
	int KillPercent; //Percentage of process kill
	int AvgUtilization; //Average utilization for all processors
	float StealLimit; // A percentage. (LQF - SQF) / LQF (should be greater than 40)
	int MigsDueMax_W; // count of migrations due to Max_W
	int MigsDueRTF; // count of migrations due to RTF;
	int StealCount; // Count of processes moved due to steal
	int ForkedCount; // Count of processes forked
	int KilledCount; // Count of processes killed

public:
	void LoadData(); // open the input file and load all processes into NEW list
	void SaveData(); // produce the output file at end of simulation
	void CreateProcessors(int, int, int);
	void Print(char); //Decides which mode ([I]nteractive - [S]ilent - Step[B]yStep) 
	void Add_toblocklist(PROCESS*blockedprocess);
	void Add_toterminatedlist(PROCESS* terminatedprocess);
	bool IO_requesthandling(PROCESS* RUN);
	bool Process_completion(PROCESS* RUN);
	bool MIG_RR_SJF(PROCESS* run);
	bool MIG_FCFS_RR(PROCESS* run);
	int get_TIMESTEP();
	int getTimeSlice();
	int getRTF();
	int get_LiveTotalProcesses();
	void increment_LiveTotalProcesses();
	Scheduler();
	void SIMULATE();
	void CheckNewArrivals(); // Distributes processes from NEW queue to Shortest RDY 
	void Execute(); //This function iterates over all processors calling ScheduleAlgo of each one
	bool AllDone(); //All is done if RDY queues of all processors are all empty
	void AddToRunning();
	void WorkStealing();
	PROCESSOR* FindShortestProcessor(char x = 'N'); // This function if given a parameter 'S' OR 'R', finds the shortest SJF && RR respectively
	void BLKtoRDY(); //Each timestep checks if the front of BLK (process with shortest IOD) has finished its IOD request, and moves it to shortest RDY
	void CalculateStats();
	void AddToForked(PROCESS*);
	void increment_MigsDueMax_W();
	void increment_MigsDueRTF();
	void increment_StealCount();
	void increment_KilledCount();
	void increment_runningcount();
	void decrement_runningcount();
	void RemoveFromEverywhere(PROCESS*); //takes a process address as a target & makes sure it is dead and burried
	void RemoveFromRunning(PROCESS*);
	~Scheduler();
};

