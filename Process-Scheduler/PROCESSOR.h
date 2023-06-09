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
	float PLoad; //Statistic for phase 2
	float PUtil;  //Statistic for phase 2
	Scheduler* SchedPtr; //Pointer to Scheduler
	bool RunningInSched;
	int ExpectedFinishTime; //inc with CT when any process added to RDY
							//dec with CT when any process removed from RDY(as in case of kill)
	int TotalBusyTime;
	int TotalIdleTime;
	int CooldownTimer; // int n, given in the input file, the amount of time for the processor to cooldown
public:
	PROCESSOR(Scheduler*);
	~PROCESSOR();
	virtual void ScheduleAlgo() = 0;//function moving process from RDY to RUN differ for each processor type
	virtual void PrintMyReady() = 0;
	virtual void addToMyRdy(PROCESS*) = 0;
	int getRSIZE(); //get the RDY Queue size 
	string getType(); //get type of processor
	PROCESS* getCurrentlyRunning(); //returns address of currently running process for each processor, null otherwise
	bool getState();
	void setState(bool s);
	virtual bool PromoteProcess() = 0; //Makes the process AS running, and removes it from RDY queue
    void ResetRunningProcess(int); // Gets rid of currently running process and resets processor state to idle
	void setRunningInSched(int);
	bool getRunningInSched();
	int getExpectedFinishTime();
	virtual PROCESS* removeTopOfMyRDY() = 0;
	void KillRun();
	float getPLoad() const;
	float getPUtil() const;
	void CalculatePLoad(int);
	void CalculatePUtil();
	void setCooldown(int);
	int getCooldown() const;
	void decrementCooldown();
	virtual void STOP(const int) = 0; // If a processor is in stop state due to overheating
};

