#include "Scheduler.h"
#include <fstream>
#include <sstream>
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
	File = FileName;
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
		PROCESS* tmp = new PROCESS(AT, PID, CT, N); // The process constructor expects these values
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
	string ignore1;
	string ignore2;
	myFile >> ignore1 >> ignore2;
	int a, b;
	while (myFile >> a)
	{
		myFile >> b;
		TimeOfDeath.enqueue(a);
		ProcessesToBeKilled.enqueue(b);
	}
	myFile.close();
}
void Scheduler::SaveData()
{
	File = "Output_" + File;
	ofstream OutputFile;
	OutputFile.open(File, ios::out);
	if (OutputFile.is_open())
	{
		OutputFile << "TT    PID    AT    CT    IO_D        WT    RT    TRT" << endl;
		while (!TRM.isEmpty())
		{
			PROCESS* temp = TRM.dequeue(temp);
			OutputFile << temp->get_TT() << "    " << temp->get_PID() << "    " << temp->get_AT()
				<< "    " << temp->get_totalIoD() << "        " << temp->get_WT() << "    " << temp->get_TRT() << endl;
		}
		OutputFile << "Processes: " << LiveTotalProcesses << endl;
		OutputFile << "Avg WT = " << AvgWaitingTime << ",      Avg RT = " << AvgResponseTime << ",      Avg TRT = " << AvgTRT << endl;
		OutputFile << "Migration % :        RTF = " << RTF << "%,      MaxW = " << MaxW << "%" << endl;
		OutputFile << "Forked Processes: " << ForkPercent << "%" << endl;
		OutputFile << "Killed Processes: " << KillPercent << "%" << endl;
		OutputFile << endl;
		OutputFile << "Processors: " << totalProcessors << " [" << FCFS_Count << " FCFS, " << SJF_Count << " SJF, "
			<< RR_Count << " RR]" << endl;
		OutputFile << "Processors Load" << endl;
		for (int i = 1; i < totalProcessors; i++)
		{
			OutputFile << "p" << i << "=" << ListOfProcessors[i - 1]->getPLoad() << "%,  ";
		}
		OutputFile << "p" << totalProcessors << "=" << ListOfProcessors[totalProcessors - 1]->getPLoad() << "%\n";
		OutputFile << endl;
		OutputFile << "Processors Utiliz" << endl;
		for (int i = 1; i < totalProcessors; i++)
		{
			OutputFile << "p" << i << "=" << ListOfProcessors[i - 1]->getPUtil() << "%,  ";
			AvgUtilization += ListOfProcessors[i - 1]->getPUtil();
		}
		AvgUtilization += ListOfProcessors[totalProcessors - 1]->getPUtil();
		AvgUtilization = (AvgUtilization / TRM_Count) * 100;
		OutputFile << "p" << totalProcessors << "=" << ListOfProcessors[totalProcessors - 1]->getPUtil() << "%\n";
		OutputFile << "Avg utilization = " << AvgUtilization << "%";
		OutputFile.close();
	}

}
void Scheduler::CreateProcessors(int FC, int SJ, int R)
{
	int counter = 0;
	ListOfProcessors = new PROCESSOR* [FC + SJ + R];
	for (int i = 0; i < FC; i++)
	{
		FCFS* tmp = new FCFS(this);
		ListOfProcessors[counter++] = tmp;
	}
	for (int i = 0; i < SJ; i++)
	{
		SJF* tmp = new SJF(this);
		ListOfProcessors[counter++] = tmp;
	}
	for (int i = 0; i < R; i++)
	{
		RR* tmp = new RR(this);
		ListOfProcessors[counter++] = tmp;
	}
}

void Scheduler::Print(char z)
{
	if (z == 'I')
		UIptr->printInteractive(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, Running, RunningCountIndex, TRM, TRM_Count, RunningCount, ProcessesCount);
	else if (z == 'B')
		UIptr->printStepByStep(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, Running, RunningCountIndex, TRM, TRM_Count, RunningCount);
	else if (z == 'S')
	{
		UIptr->printSilent();
		SaveData();
	}
}

void Scheduler::Add_toblocklist(PROCESS* blockedprocess)
{
	//BLK.enqueue(blockedprocess, blockedprocess->get_totalIoD() * - 1); // Priority queue ranks descending but here we want highest priority to be least IOD
	BLK.enqueue(blockedprocess);
	BLK_Count++;
}

void Scheduler::Add_toterminatedlist(PROCESS* temp)
{
	TRM.enqueue(temp, temp->get_TT());
	TRM_Count++;
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
	AvgWaitingTime = 0;
	AvgResponseTime = 0;
	AvgTRT = 0;
	MigPercent_MaxW = 0;
	MigPercent_RTF = 0;
	MigsDueMax_W = 0;
	MigsDueRTF = 0;
	ForkedCount = 0;
	StealCount = 0;
	KilledCount = 0;
	KillPercent = 0;
	StealPercent = 0;
}
bool Scheduler:: IO_requesthandling(PROCESS* RUN) {
	if (RUN->get_N() > 0 && RUN->get_countN() <= RUN->get_N())
	{
		if (RUN->get_countsteps() == RUN->get_IO_R(RUN->get_countN()))
		{
			RUN->incrementCountsteps(1);
			RUN->incrementcountN();
			//Add_toblocklist(RUN); The BLK is now priority queue. Highest priority is Least remaining IOD
			RunningCount--;
			return true;
		}
	}
	return false;
}

bool Scheduler::Process_completion(PROCESS* RUN)
{
	if (RUN->get_countsteps() > RUN->get_CT())
	{
		Add_toterminatedlist(RUN);
		RunningCount--;
		return true;
	}
	return false;
}

bool Scheduler::MIG_RR_SJF(PROCESS* run)
{
	if ((run->get_CT() - run->get_countsteps()) < RTF)
	{
		FindShortestProcessor('S')->addToMyRdy(run);
		return true;
	}
	return false;
}

bool Scheduler::MIG_FCFS_RR(PROCESS* run)
{
	if (run->get_WT()>MaxW)
	{
		FindShortestProcessor('R')->addToMyRdy(run);
		return true;
	}
	return false;
}


void Scheduler::SIMULATE()
{
	int RunMode = UIptr->SelectRunMode(); // Returns 1 for Interactive, 2 for Step-By-Step, 3 for Silent. 0 otherwise;
	LoadData(); //Step 1 Load Data from Input File
	CreateProcessors(FCFS_Count, SJF_Count, RR_Count); // Step 2 Create the given Processors
	while (!AllDone())
	{
		CheckNewArrivals(); //Step 3 Move processes with AT equaling Timestep to RDY Queue (Their time has come :) )
		Execute(); //Iterates over all processors and move Rdy processes to Running if possible
		AddToRunning();   //Iterates over all runnings of processors and add them to RUNNING array
		BLKtoRDY();
		switch (RunMode)
		{
		case 1:
			Print('I');
			break;
		case 2:
			Print('B');
			break;
		case 3:
			Print('S');
			break;
		default:
			break;
		}
		TIMESTEP++;
	}
	CalculateStats(); // Calculate all statistics displayed in the output file
	SaveData(); // Produce the Output file
}

void Scheduler::CheckNewArrivals()
{
	if (NEW.isEmpty())
		return;
	PROCESS* temp;
	NEW.dequeue(temp);
	FindShortestProcessor()->addToMyRdy(temp); // Shortest Processor RDY gets first elem in NEW queue
}

void Scheduler::Execute()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		ListOfProcessors[i]->ScheduleAlgo();
	}
}
/*
void Scheduler::AllocatingProcesses() //Do NOT delete it just yet, we need the same conditions in phase 2, so keep it till we're DONE.
{
	for (int i = 0; i < RunningCountIndex; i++) 
		//RunningCountIndex may be changed to become totalProcessors (if agree with me do it)
	{
		if (!Running[i])
			continue;
		if (RunningCount > 0 && i<totalProcessors)
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

				TRM.enqueue(Running[i], Running[i]->get_TT());
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
	
	for (int i = 0; i < FCFS_Count; i++)
	{
		PROCESS* KILLED = dynamic_cast<FCFS*>(ListOfProcessors[i])->KillRandomly(FCFS_random);
		if (KILLED)
		{
			TRM.enqueue(KILLED, KILLED->get_TT());
			TRM_Count++;
		}
	}
}
*/
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
				if (Running[newRunningCountIndex] == nullptr) {
					Running[newRunningCountIndex] = ListOfProcessors[i]->getCurrentlyRunning();
					RunningCountIndex++;
					ListOfProcessors[i]->setRunningInSched(1);
				}
				else {
					RunningCountIndex++;
					newRunningCountIndex = RunningCountIndex % totalProcessors;
					if (Running[newRunningCountIndex] == nullptr) {
						Running[newRunningCountIndex] = ListOfProcessors[i]->getCurrentlyRunning();
						RunningCountIndex++;
						ListOfProcessors[i]->setRunningInSched(1);
					}
				}
			}
			else
			{
				Running[RunningCountIndex++] = ListOfProcessors[i]->getCurrentlyRunning();
				ListOfProcessors[i]->setRunningInSched(1);
			}
		}
	}
	
}

void Scheduler::WorkStealing()
{
	if (TIMESTEP % STL == 0) //every STL timestep
	{
		int LQF=-1;
		int SQF=1e9;
		int indxProcessorOfSQF;
		int indxProcessorOfLQF;
		for (int i = 0;i < totalProcessors;i++) {
			int cur = ListOfProcessors[i]->getExpectedFinishTime();
			if (cur >= LQF) {
				LQF = cur;
				indxProcessorOfLQF = i;
			}
			if (cur <= SQF) {
				SQF = cur;
				indxProcessorOfSQF = i;
			}
		}
		StealLimit = (LQF - SQF) / LQF;
		while (StealLimit > 0.4) {
			PROCESS* topLQF = ListOfProcessors[indxProcessorOfLQF]->removeTopOfMyRDY();
			ListOfProcessors[indxProcessorOfSQF]->addToMyRdy(topLQF);
			LQF = ListOfProcessors[indxProcessorOfLQF]->getExpectedFinishTime();
			SQF = ListOfProcessors[indxProcessorOfSQF]->getExpectedFinishTime();
			StealLimit = (LQF - SQF) / LQF;
		}
	}
}

PROCESSOR* Scheduler::FindShortestProcessor(char x = 'N')
{
	/*
	This function is supposed to return the first to finish SJF and RR processors if given 'S' and 'R' respectively.
	Else it finds the overall first to finish processor
	*/
	if (x == 'S')
	{
		int shortestProcessor = INT_MAX; // Keeps track of the first SJF processor to finish
		int shortestProcessorIndex = 0; // Index of the shortest SJF
		for (int i = 1; i < totalProcessors; i++)
		{
			if (ListOfProcessors[i]->getExpectedFinishTime() < shortestProcessor && ListOfProcessors[i]->getType() == "SJF")
			{
				shortestProcessor = ListOfProcessors[i]->getExpectedFinishTime();
				shortestProcessorIndex = i;
			}
		}
		return ListOfProcessors[shortestProcessorIndex];
	}
	else if (x == 'R')
	{
		int shortestProcessor = INT_MAX; // Keeps track of the first RR processor to finish
		int shortestProcessorIndex = 0; // Index of the shortest RR
		for (int i = 1; i < totalProcessors; i++)
		{
			if (ListOfProcessors[i]->getExpectedFinishTime() < shortestProcessor && ListOfProcessors[i]->getType() == "RR")
			{
				shortestProcessor = ListOfProcessors[i]->getExpectedFinishTime();
				shortestProcessorIndex = i;
			}
		}
		return ListOfProcessors[shortestProcessorIndex];
	}
	int shortestProcessor = ListOfProcessors[0]->getExpectedFinishTime(); // Keeps track of the processor that will finish first
	int shortestProcessorIndex = 0; // Index of the shortest processor
	for (int i = 1; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i]->getExpectedFinishTime() < shortestProcessor)
		{
			shortestProcessor = ListOfProcessors[i]->getExpectedFinishTime();
			shortestProcessorIndex = i;
		}
	}
	return ListOfProcessors[shortestProcessorIndex];
}

void Scheduler::BLKtoRDY()
{
	PROCESS* tmp;
	if (BLK.peek(tmp))
	{
		if (!tmp->get_totalIoD()) //checks if the processor IOD == 0, moves it to shortest RDY
		{
			BLK.dequeue(tmp);
			BLK_Count--;
			FindShortestProcessor()->addToMyRdy(tmp);
		}
	}
}

void Scheduler::CalculateStats()
{
	for (int i = 0; i < TRM_Count; i++)
	{
		PROCESS* temp;
		TRM.dequeue(temp);
		AvgWaitingTime += temp->get_WT();
		AvgResponseTime += temp->get_RT();
		AvgTRT += temp->get_TRT();
	}
	AvgWaitingTime /= TRM_Count;
	AvgResponseTime /= TRM_Count;
	AvgTRT /= TRM_Count;
	MigPercent_MaxW = (MigsDueMax_W / TRM_Count) * 100;
	MigPercent_RTF = (MigsDueRTF / TRM_Count) * 100;
	StealPercent = (StealCount / TRM_Count) * 100;
	Forkability = (ForkedCount / TRM_Count) * 100;
	KillPercent = (KilledCount / TRM_Count) * 100;
	
}

void Scheduler::AddToForked(PROCESS* tmp)
{
	ForkedProcesses.InsertEnd(tmp);
	ForkedCount++;
}

void Scheduler::increment_MigsDueMax_W()
{
	MigsDueMax_W++;
}

void Scheduler::increment_MigsDueRTF()
{
	MigsDueRTF++;
}

void Scheduler::increment_StealCount()
{
	StealCount++;
}

void Scheduler::increment_KilledCount()
{
	KilledCount++;
}

void Scheduler::RemoveFromEverywhere(PROCESS* target)
{
	for (int i = 0; i < FCFS_Count; i++)
	{
		if (ListOfProcessors[i]->getRun() == target)
		{
			ListOfProcessors[i]->KillRun();
			return;
		}
		if (dynamic_cast<FCFS*>(ListOfProcessors[i])->isInMyRdy(target))
			return;
	}
}

Scheduler::~Scheduler()
{
	Running = nullptr;
	delete[] Running;
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i])
		{
			delete ListOfProcessors[i];
			ListOfProcessors[i] = nullptr;
		}
	}
	delete[] ListOfProcessors;
	TRM.~LinkedPriorityQueue();
}