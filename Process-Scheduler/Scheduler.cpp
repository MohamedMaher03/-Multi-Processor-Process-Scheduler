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

int Scheduler::increase_TIMESTEP_RR()
{
	TIMESTEP += TimeSlice;
	return TIMESTEP;
}

