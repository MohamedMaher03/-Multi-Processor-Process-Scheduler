#include "Scheduler.h"
#include <fstream>
#include <sstream>
using namespace std;

void Scheduler::LoadData()
{
	string FileName = UIptr->ReadFileName();
	ifstream myFile(FileName, ios::in);
	if (!myFile.is_open())
	{
		UIptr->PrintMessage("File Not Found!");
		return;
	}
	myFile >> FCFS_Count >> SJF_Count >> RR_Count;
	totalProcessors = FCFS_Count + SJF_Count + RR_Count;
	myFile >> TimeSlice;
	myFile >> RTF >> MaxW >> STL >> Forkability;
	myFile >> ProcessesCount;
	
	for (int i = 0; i < ProcessesCount; i++)
	{
		int AT, PID, CT, N;
		myFile >> AT >> PID >> CT >> N;
		PROCESS* tmp = new PROCESS(AT, PID, CT, N); //I assume the constructor to take these values
		NEW.enqueue(tmp);//Processes are first added to NEW queue
		string IO;
		myFile >> IO;
		stringstream ss(IO);
		for (int j = 0; j < N; j++)
		{
			int x, y;
			char c1, c2, c3;
			ss >> c1 >> x >> c2 >> y >> c3;
			//Creator of class process is expected to create 2 arrays of size N
			//First array ==> IO_R, Second array ==> IO_D
			tmp->set_IO_R(x, j);
			tmp->set_IO_D(y, j);
		}
		string ignore1, ignore2;
		myFile >> ignore1 >> ignore2;
		int a, b;
		while (myFile >> a)
		{
			myFile >> b;
			TimeOfDeath.enqueue(a);
			ProcessesToBeKilled.enqueue(b);
		}
		
	}
}
void Scheduler::SaveData()
{

}
void Scheduler::CreateProcessors(int FC, int SJ, int R)
{
	int counter = 0;
	for (int i = 0; i < FC; i++)
	{
		FCFS tmp;
		ListOfProcessors[counter] = &tmp;
	}
	for (int i = 0; i < SJ; i++)
	{
		SJF tmp;
		ListOfProcessors[counter] = &tmp;
	}
	for (int i = 0; i < R; i++)
	{
		RR tmp;
		ListOfProcessors[counter] = &tmp;
	}
}

void Scheduler::Print(char z)
{
	if (z == 'I')
		UIptr->printInteractive(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, Running, RunningCount, TRM, TRM_Count);
	else if (z == 'B')
		UIptr->printStepByStep(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, Running, RunningCount, TRM, TRM_Count);
	else if (z == 'S')
		UIptr->printSilent();
}

void Scheduler::Add_toblocklist(PROCESS* blockedprocess)
{
	BLK.enqueue(blockedprocess);
}

void Scheduler::Add_toterminatedlist(PROCESS* terminatedprocess)
{
	TRM.enqueue(terminatedprocess);
}

int Scheduler::get_TIMESTEP()
{
	return TIMESTEP;
}
int Scheduler::getTimeSlice()
{
	return TimeSlice;
}

int Scheduler::getRTF()
{
	return RTF;
}
Scheduler::Scheduler()
{
	Running = new int[totalProcessors];
}

void Scheduler::UpdateRunningProcesses()
{
	int count = 0;
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i]->getCurrentlyRunning())
		{
			Running[count++] = ListOfProcessors[i]->getCurrentlyRunning()->get_PID();
		}
	}
	RUN_Count = count;
}

void Scheduler::SIMULATE()
{
	int count = 0; //count to randomize process in the processors
	int new_curindx = 0;
	LoadData(); //Step 1 Load Data from Input File
	while (!AllDone()) 
	{
		CheckNewArrivals(count, new_curindx); //Step 2 Move processes with AT equaling Timestep to RDY Queue (Their time has come :) )
		PromoteRdyToRun(); //Iterates over all processors and move Rdy processes to Running
		Print('B'); // Print in Step-By-Step Mode
		TIMESTEP++;
	}
}

void Scheduler::CheckNewArrivals(int&count,int& new_curindx)
{
	/*
	int count = 0;
	for (int i = 0; i < ProcessesCount; i++)
	{
		PROCESS* tmp;
		NEW.peek(tmp);
		if (tmp->get_AT() == TIMESTEP)
		{
			ListOfProcessors[count++]->addToMyRdy(tmp); //Adds process to ready of each processor (Randomly ofc)
			NEW.dequeue(tmp);
		}
	}
	*/
	for (int i = new_curindx;i < ProcessesCount;i++) {
		PROCESS* tmp;
		NEW.peek(tmp);
		if (tmp->get_AT() == TIMESTEP) {
			ListOfProcessors[count]->addToMyRdy(tmp); //Adds process to ready of each processor (Randomly ofc)
			count = (count + 1) % ProcessesCount;
			new_curindx++;
			NEW.dequeue(tmp);
		}
		else {
			break;
		}
	}
}

bool Scheduler::PromoteRdyToRun()
{
	PROCESS* tmp;
	for (int i = 0; i < totalProcessors; i++)
	{
		if (!ListOfProcessors[i]->getState()) //If getState == false, means the processor is idle
		{
			ListOfProcessors[i]->PromoteProcess();
			return true;
		}
	}
	
	return false;
}

bool Scheduler::AllDone()
{
	return TRM_Count == ProcessesCount;
}

Scheduler::~Scheduler()
{
	delete[] Running;
}