#include "Scheduler.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <random>
using namespace std;
class FCFS;
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
	LiveTotalProcesses = ProcessesCount; //updated 
	for (int i = 0; i < ProcessesCount; i++)
	{
		int AT, PID, CT, N;
		myFile >> AT >> PID >> CT >> N;
		PROCESS* tmp = new PROCESS(AT, PID, CT, N); //I assume the constructor to take these values
		NEW.enqueue(tmp);//Processes are first added to NEW queue
		if (N > 0)
		{ 
			string IO;
			myFile >> IO;
			stringstream ss(IO);
			for (int j = 0; j < N; j++)
			{
				int x, y;
				char c1, c2, c3;
				ss >> c1 >> x >> c2 >> y >> c3;
				tmp->set_IO(x, y, j);
				if (j + 1 < N)
				{
					char c4;
					ss >> c4;
				}
			}
		}
		
		
	}
	//string ignore1, ignore2;
	//myFile >> ignore1 >> ignore2;
	int a, b;
	while (myFile >> a)
	{
		myFile >> b;
		TimeOfDeath.enqueue(a);
		ProcessesToBeKilled.enqueue(b);
	}
}
void Scheduler::SaveData()
{

}
void Scheduler::CreateProcessors(int FC, int SJ, int R)
{
	int counter = 0;
	ListOfProcessors = new PROCESSOR* [FC + SJ + R];
	for (int i = 0; i < FC; i++)
	{
		FCFS* tmp = new FCFS();
		ListOfProcessors[counter++] = tmp;
	}
	for (int i = 0; i < SJ; i++)
	{
		SJF* tmp = new SJF();
		ListOfProcessors[counter++] = tmp;
	}
	for (int i = 0; i < R; i++)
	{
		RR* tmp = new RR();
		ListOfProcessors[counter++] = tmp;
	}
}

void Scheduler::Print(char z)
{
	if (z == 'I')
		UIptr->printInteractive(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, Running, RunningCountIndex, TRM, TRM_Count, RunningCount);
	else if (z == 'B')
		UIptr->printStepByStep(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, Running, RunningCountIndex, TRM, TRM_Count, RunningCount);
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
	TIMESTEP = 1;
	Running = new PROCESS*[totalProcessors];
	for (int i = 0; i < totalProcessors; i++)
	{
		Running[i] = nullptr;
	}
	TRM_Count = 0;
	BLK_Count = 0;
	FCFS_Count = 0;
	SJF_Count = 0;
	RR_Count = 0;
	ProcessesCount = 0;
	RunningCount = 0;
	RunningCountIndex = 0;
	LiveTotalProcesses = 0;
}

void Scheduler::UpdateRunningProcesses()
{
	/*for (int i = 0; i < totalProcessors; i++)
	{
		ListOfProcessors[i]->ResetRunningProcess();
	}
	*/
}
void Scheduler::SIMULATE()
{
	int count = 0; //count to randomize process in the processors
	LoadData(); //Step 1 Load Data from Input File
	CreateProcessors(FCFS_Count, SJF_Count, RR_Count);
	while (!AllDone())
	{
		CheckNewArrivals(count); //Step 2 Move processes with AT equaling Timestep to RDY Queue (Their time has come :) )
		PromoteRdyToRun(); //Iterates over all processors and move Rdy processes to Running if possible
		AddToRunning();   //Iterates over all runnings of processors and add them to RUNNING array
		AllocatingProcesses(count); //Iterates over all processes and move them based on randomizer result
		//UpdateRunningProcesses(); //Updates current processors' states
		Print('I'); // Print in Interactive Mode
		TIMESTEP++;
	}
	Print('I'); // Print in Interactive Mode
}

void Scheduler::CheckNewArrivals(int&count)
{
	PROCESS* tmp;
	if(NEW.peek(tmp))
	while(tmp->get_AT() == TIMESTEP)
	{
		if (!NEW.dequeue(tmp)) {
			break;
		}
		ListOfProcessors[count]->addToMyRdy(tmp); //Adds process to ready of each processor (Randomly ofc)
		count = (count + 1) % totalProcessors;
		NEW.peek(tmp);
	}
}

void Scheduler::PromoteRdyToRun()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i]->getRSIZE() > 0)
			if (ListOfProcessors[i]->PromoteProcess(TIMESTEP))
				RunningCount++;
				
	}
}

int Scheduler::Randomize()
{
	random_device rd;
	mt19937 gen(rd());

	// Define the distribution for the random number
	uniform_int_distribution<> dis(1, 100);

	// Generate and return the random number
	return dis(gen);
}

void Scheduler::AllocatingProcesses(int&count)
{
	for (int i = 0; i < RunningCountIndex; i++) 
		//RunningCountIndex may be changed to become totalProcessors (if agree with me do it)
	{
		int random = Randomize();
		if (RunningCount > 0 && i<totalProcessors &&Running[i])
		{
			if (random >= 1 && random <= 15)
			{
				//MOVE Running[i] to BLK list
				BLK.enqueue(Running[i]);
				BLK_Count++;
				for (int j = 0; j < totalProcessors; j++) //Remove running process from it's original processor RUN*
				{
					ListOfProcessors[j]->ResetRunningProcess(Running[i]->get_PID());
				}
				Running[i] = nullptr;
				if (RunningCount > 0)
					RunningCount--;

			}
			else if (random >= 20 && random <= 30)
			{
				//MOVE Running[i] to RDY list of any processor

				ListOfProcessors[count]->addToMyRdy(Running[i]);
				count = (count + 1) % totalProcessors;
				for (int j = 0; j < totalProcessors; j++)
				{
					ListOfProcessors[j]->ResetRunningProcess(Running[i]->get_PID());
				}
				Running[i] = nullptr;
				if (RunningCount > 0)
					RunningCount--;

			}
			else if (random >= 50 && random <= 60)
			{
				//MOVE Running[i] to TRM list

				TRM.enqueue(Running[i]);
				TRM_Count++;
				for (int j = 0; j < totalProcessors; j++)
				{
					ListOfProcessors[j]->ResetRunningProcess(Running[i]->get_PID());
				}
				Running[i] = nullptr;
				if (RunningCount > 0)
					RunningCount--;

			}
		}
	}
	int LiveBlkCount = BLK_Count;
	for (int i = 0; i < LiveBlkCount; i++)
	{
		int random = Randomize();
		if (random <= 10)
		{
			//Move BLK[i] to RDY
			/*if (BLK.isEmpty())
				return;*/
			PROCESS* tmp;
			BLK.dequeue(tmp);
			BLK_Count--;
			ListOfProcessors[count]->addToMyRdy(tmp);
			count = (count + 1) % totalProcessors;
			tmp = nullptr;
		}
	}
	int FCFS_random = Randomize();
	FCFS_random %= LiveTotalProcesses;
	FCFS_random++;
	for (int i = 0; i < FCFS_Count; i++)
	{
		PROCESS* KILLED = dynamic_cast<FCFS*>(ListOfProcessors[i])->KillRandomly(FCFS_random);
		if (KILLED)
		{
			TRM.enqueue(KILLED);
			TRM_Count++;
		}
	}
}

bool Scheduler::AllDone()
{
	
	return TRM_Count == ProcessesCount;
}

void Scheduler::AddToRunning()
{
	for (int i = 0; i < totalProcessors; i++)  
	{
		if (ListOfProcessors[i]->getState() && !ListOfProcessors[i]->getRunningInSched())
		{
			if (RunningCountIndex >= totalProcessors)
			{
				int newRunningCountIndex = RunningCountIndex % totalProcessors;
				Running[newRunningCountIndex] = ListOfProcessors[i]->getCurrentlyRunning();
				RunningCountIndex++;
				ListOfProcessors[i]->setRunningInSched(1);
			}
			else
			{
				Running[RunningCountIndex++] = ListOfProcessors[i]->getCurrentlyRunning();
				ListOfProcessors[i]->setRunningInSched(1);
			}
		}
	}
	
}

Scheduler::~Scheduler()
{
	delete[] Running;
}