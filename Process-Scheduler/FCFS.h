#pragma once
#include "PROCESSOR.h"
#include "LinkedList.h"
#include "LinkedQueue.h"
#include "Pair.h"

class FCFS :public PROCESSOR
{
private:
	LinkedList <PROCESS*> RDY;
	static LinkedQueue<Pair*> ToBeKilled;
	
public: 
	FCFS(Scheduler*);
	~FCFS();
	void ScheduleAlgo() override;
	void addToMyRdy(PROCESS *P) override;
	void PrintMyReady() override;
	bool PromoteProcess();
	void Kill(PROCESS*);
	bool KillSignal(int, int);
	PROCESS* removeTopOfMyRDY() override;
	void Killchildren(PROCESS* P); // Calls the Kill function for all children of a process
	bool isInMyRdy(PROCESS*); // Returns true if a certain process is in its RDY list and kills it
	void addToBeKilled(Pair*);
	void ForkTree(PROCESS* P);
	void RemoveFromMyRdy(PROCESS*); // Removes a certain process from its ready
	int random();
	virtual PROCESS* find_first_nonforked_elemnt();
};

