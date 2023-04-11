#include "Scheduler.h"
#include <fstream>
#include <sstream>
#include<cstdlib>
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
			tmp->set_IO(x, y, j);
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
	//else if (z == 'S')
		//UIptr->printSilent();
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
	Running = new PROCESS*[totalProcessors];
	BLK_Count = 0;
	FCFS_Count = 0;
	SJF_Count = 0;
	RR_Count = 0;
	ProcessesCount = 0;
	RunningCount = 0;
}

void Scheduler::UpdateRunningProcesses()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		ListOfProcessors[i]->ResetRunningProcess();
	}
}
void Scheduler::SIMULATE()
{
	int count = 0; //count to randomize process in the processors
	LoadData(); //Step 1 Load Data from Input File
	while (!AllDone()) 
	{
		CheckNewArrivals(count); //Step 2 Move processes with AT equaling Timestep to RDY Queue (Their time has come :) )
		PromoteRdyToRun(); //Iterates over all processors and move Rdy processes to Running if possible
		AllocatingProcesses(); //Iterates over all processes and move them based on randomizer result
		UpdateRunningProcesses(); //Updates current processors' states
		Print('B'); // Print in Step-By-Step Mode
		TIMESTEP++;
	}
}

void Scheduler::CheckNewArrivals(int&count)
{
	PROCESS* tmp;
	NEW.peek(tmp);
	while(tmp->get_AT() == TIMESTEP)
	{
		ListOfProcessors[count]->addToMyRdy(tmp); //Adds process to ready of each processor (Randomly ofc)
		count = (count + 1) % totalProcessors;
		NEW.dequeue(tmp);
		NEW.peek(tmp);
	}
}

void Scheduler::PromoteRdyToRun()
{
	PROCESS* tmp;
	for (int i = 0; i < totalProcessors; i++)
	{
		ListOfProcessors[i]->PromoteProcess();
	}
}

int Scheduler::Randomize()
{
	// Providing a seed value
	srand((unsigned)time(NULL));

	// Get a random number
	int random = (rand() % 100) + 1;

	// Print the random number
	return random;
}

void Scheduler::AllocatingProcesses()
{
	int count = 0; //Counter that iterates over processors to add to their readies evenly
	for (int i = 0; i < RunningCount; i++)
	{
		int random = Randomize();
		if (random >= 1 && random <= 15)
		{
			//MOVE Running[i] to BLK list
			BLK.enqueue(Running[i]);
			Running[i] = nullptr;
			RunningCount--;
		}
		else if (random >= 20 && random <= 30)
		{
			//MOVE Running[i] to RDY list of any processor
			ListOfProcessors[count]->addToMyRdy(Running[i]);
			count = (count + 1) % totalProcessors;
			Running[i] = nullptr;
			RunningCount--;
		}
		else if (random >= 50 && random <= 60)
		{
			//MOVE Running[i] to TRM list
			TRM.enqueue(Running[i]);
			Running[i] = nullptr;
			RunningCount--;
		}
		else if (random <= 10 && !BLK.isEmpty())
		{
			//Move BLK[i] to RDY
			
			PROCESS* tmp;
			BLK.dequeue(tmp);
			ListOfProcessors[count]->addToMyRdy(tmp);
			count = (count + 1) % totalProcessors;
		}
	}
}

bool Scheduler::AllDone()
{
	return TRM_Count == LiveTotalProcesses;
}

void Scheduler::AddToRunning(PROCESS* tmp)
{
	Running[RunningCount++] = tmp;
}

Scheduler::~Scheduler()
{
	delete[] Running;
}