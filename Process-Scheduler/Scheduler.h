#pragma once
#include "LinkedQueue.h"
#include "PROCESS.h"
#include "PROCESSOR.h"
#include "UI.h"
#include "PROCESS.h"
#include "FCFS.h"
#include "SJF.h"
#include "RR.h"
#include "EDF.h"
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
	int EDF_count;
	int TimeSlice;
	int RTF;
	int MaxW;
	int STL;
	int Forkability;
	int ProcessesCount;
	int BLK_Count;
	int TRM_Count;
	int RunningCount; // Total number of currently running processes
	int TotalTRT;
	int LiveTotalProcesses;
	int BeforeDeadline;
	int coolTime; // The amount of time a processor needs to cool down
	string File;  // The name of the input file and will be used as the name of output file too
	//--------- STATISTICS -------------
	float AvgWaitingTime; //Average waiting time for all processes
	float AvgResponseTime; //Average Response time for all processes
	float AvgTRT; //Average Turnaround time for all processes
	float MigPercent_RTF; //Percentage of process migration due to RTF
	float MigPercent_MaxW; //Percentage of process migration due to MaxW
	float StealPercent; //Percentages of processes moved by works steal
	float ForkPercent; //Percentage of process fork
	float KillPercent; //Percentage of process kill
	float AvgUtilization; //Average utilization for all processors
	float StealLimit; // A percentage. (LQF - SQF) / LQF (should be greater than 40)
	float MigsDueMax_W; // count of migrations due to Max_W
	float MigsDueRTF; // count of migrations due to RTF;
	int StealCount; // Count of processes moved due to steal
	int ForkedCount; // Count of processes forked
	int KilledCount; // Count of processes killed
	float BeforeDeadlinePercent; // Percentage of processes completed before their deadline

public:
	void LoadData(); // open the input file and load all processes into NEW list
	void SaveData(); // produce the output file at end of simulation
	void CreateProcessors(int, int, int,int);
	void Print(char); //Decides which mode ([I]nteractive - [S]ilent - Step[B]yStep) 
	void Add_toblocklist(PROCESS*blockedprocess);
	void Add_toterminatedlist(PROCESS* terminatedprocess);
	bool IO_requesthandling(PROCESS* RUN);
	bool Process_completion(PROCESS* RUN);
	bool MIG_RR_SJF(PROCESS* run);
	bool MIG_FCFS_RR(PROCESS* run);
	int get_TIMESTEP() const;
	int getTimeSlice();
	int getRTF();
	int get_LiveTotalProcesses();
	int get_ForkPercent() const;
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
	void increment_MigsDueMax_W();
	void increment_MigsDueRTF();
	void increment_StealCount();
	void increment_KilledCount();
	void increment_runningcount();
	void decrement_runningcount();
	void RemoveFromEverywhere(PROCESS*); //takes a process address as a target & makes sure it is dead and burried
	void RemoveFromRunning(PROCESS*);
	bool check_is_SJF();//check if there is SJF processors for migration
	bool check_is_RR();//check if there is RR processors for migration
	int get_WT_RR(PROCESS* running);//get the waiting time for migration to RR
	void CreateNewProcess(PROCESS*);  //Creates a child process given its parent
	int GetTRT();
	void incrementBeforeDeadline();
	int random();
	int getCoolTime() const;
	~Scheduler();
};

