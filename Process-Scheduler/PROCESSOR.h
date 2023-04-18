#pragma once
#include "PROCESS.h"

class Scheduler; //FORWARD DECLARARTION!!!!!! 

class PROCESSOR
{
protected:
	PROCESS* RUN; 
	string TYPE;
	int RSIZE;
	bool STATE; // 0->IDLE |_||_| 1->BUSY
	int PLoad; //Statistic for phase 2
	int PUtil;  //Statistic for phase 2
	Scheduler* SchedPtr; //Pointer to Scheduler
	bool RunningInSched;
public:
	PROCESSOR();
	~PROCESSOR();
	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual void PrintMyReady() = 0;
	virtual void addToMyRdy(PROCESS*) = 0;
	int getRSIZE(); //get the RDY Queue size 
	string getType(); //get type of processor
	PROCESS* getCurrentlyRunning(); //returns address of currently running process for each processor, null otherwise
	bool getState();
	virtual bool PromoteProcess(int) = 0; //Makes the process AS running, and removes it from RDY queue
    void ResetRunningProcess(int); // Gets rid of currently running process and resets processor state to idle
	void setRunningInSched(int);
	bool getRunningInSched();

};

