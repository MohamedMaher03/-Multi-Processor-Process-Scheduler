#include "Scheduler.h"
#include <fstream>
#include <sstream>
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
	File = FileName;
	myFile >> FCFS_Count >> SJF_Count >> RR_Count >> EDF_count;
	totalProcessors = FCFS_Count + SJF_Count + RR_Count + EDF_count;
	myFile >> TimeSlice;
	myFile >> RTF >> MaxW >> STL >> Forkability >> coolTime;
	myFile >> ProcessesCount;
	LiveTotalProcesses = ProcessesCount; //updated 
	for (int i = 0; i < ProcessesCount; i++)
	{
		int AT, PID, CT,D, N;
		myFile >> AT >> PID >> CT >> D >> N;
		PROCESS* tmp = new PROCESS(AT, PID, CT, D, N); // The process constructor expects these values
		NEW.enqueue(tmp);//Processes are first added to NEW queue
		if (N > 0)
		{ 
			string IO;
			myFile >> IO;
			stringstream ss(IO);
			int Iod_total = 0;
			for (int j = 0; j < N; j++)
			{
				int x, y;
				char c1, c2, c3;
				ss >> c1 >> x >> c2 >> y >> c3;
				tmp->set_IO(x, y, j);
				Iod_total += y;
				if (j + 1 < N)
				{
					char c4;
					ss >> c4;
				}
			}
			tmp->setTotalIO_D(Iod_total);
		}
	}
	CreateProcessors(FCFS_Count, SJF_Count, RR_Count, EDF_count);
	string ignore1;
	string ignore2;
	myFile >> ignore1 >> ignore2;
	int time, id;
	if(FCFS_Count > 0)
	while (myFile >> time)
	{
		myFile >> id;
		Pair* tmp = new Pair(time, id);
		dynamic_cast<FCFS*>(ListOfProcessors[0])->addToBeKilled(tmp);
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
		OutputFile << "TT\t"  << "PID\t" << "AT\t" << "CT\t" << "IO_D\t\t" << "WT\t" << "RT\t" << "TRT\t" << endl;
		while (!TRM.isEmpty())
		{
			PROCESS* temp;
			TRM.dequeue(temp);
			OutputFile << temp->get_TT() << "\t" << temp->get_PID() << "\t" << temp->get_AT() << "\t" << temp->get_CT()
				<< "\t" << temp->get_totalIoD() << "\t\t" << temp->get_WT() << "\t" << temp->get_RT() << "\t" << temp->get_TRT() << endl;
		}
		OutputFile << "Processes: " << LiveTotalProcesses << endl;
		OutputFile << "Avg WT = " << (int)AvgWaitingTime << ",      Avg RT = " << (int)AvgResponseTime << ",      Avg TRT = " << (int)AvgTRT << endl;
		OutputFile << "Migration % :        RTF = " << (int)MigPercent_RTF << "%,      MaxW = " << (int)MigPercent_MaxW << "%" << endl;
		OutputFile << "Work Steal % : " << (int)StealPercent << "%" << endl;
		OutputFile << "Forked Processes: " << (int)ForkPercent << "%" << endl;
		OutputFile << "Killed Processes: " << (int)KillPercent << "%" << endl;
		OutputFile << "Before Deadline Processes: " << (int)BeforeDeadlinePercent << "%" << endl;
		OutputFile << endl;
		OutputFile << "Processors: " << totalProcessors << " [" << FCFS_Count << " FCFS, " << SJF_Count << " SJF, "
			<< RR_Count << " RR, " << EDF_count << " EDF]" << endl;
		OutputFile << "Processors Load" << endl;
		for (int i = 1; i < totalProcessors; i++)
		{
			OutputFile << "p" << i << "=" << (int)ListOfProcessors[i - 1]->getPLoad() << "%,  ";
		}
		OutputFile << "p" << totalProcessors << "=" << (int)ListOfProcessors[totalProcessors - 1]->getPLoad() << "%\n";
		OutputFile << endl;
		OutputFile << "Processors Utiliz" << endl;
		for (int i = 1; i < totalProcessors; i++)
		{
			OutputFile << "p" << i << "=" << (int)ListOfProcessors[i - 1]->getPUtil() << "%,  ";
			AvgUtilization += ListOfProcessors[i - 1]->getPUtil();
		}
		AvgUtilization += ListOfProcessors[totalProcessors - 1]->getPUtil();
		AvgUtilization /= totalProcessors;
		OutputFile << "p" << totalProcessors << "=" << (int)ListOfProcessors[totalProcessors - 1]->getPUtil() << "%\n";
		OutputFile << "Avg utilization = " << AvgUtilization << "%";
		OutputFile.close();
	}

}

void Scheduler::CreateProcessors(int FC, int SJ, int R,int ED)
{
	int counter = 0;
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
	for (int i = 0; i < ED; i++)
	{
		EDF* tmp = new EDF(this);
		ListOfProcessors[counter++] = tmp;
	}
	for (int i = 0; i < (FC + SJ + R +ED); i++)
	{
		RUNNING[i] = 0;
	}
}

void Scheduler::Print(char z)
{
	if (z == 'I')
		UIptr->printInteractive(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, RUNNING, TRM, TRM_Count, RunningCount);
	else if (z == 'B')
		UIptr->printStepByStep(TIMESTEP, ListOfProcessors, totalProcessors, BLK, BLK_Count, RUNNING, TRM, TRM_Count, RunningCount);
	else if (z == 'S')
	{
		UIptr->printSilent();
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
	temp->set_TT(TIMESTEP);
	int AT = temp->get_AT();
	int TRT = TIMESTEP - AT;
	temp->SetTRT(TRT);
	TotalTRT += temp->get_TRT();
	temp->setWT(TRT - temp->get_countsteps());
	if (temp->get_RT() == -1) //It should not have RT, it was killed before going into the RUN
		temp->set_RT(0);
	TRM.enqueue(temp);
	TRM_Count++;
}

int Scheduler::get_TIMESTEP() const
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

int Scheduler::get_LiveTotalProcesses()
{
	return LiveTotalProcesses;
}

int Scheduler::get_ForkPercent() const
{
	return Forkability;
}

void Scheduler::increment_LiveTotalProcesses()
{
	LiveTotalProcesses++;
}

Scheduler::Scheduler()
{
	TIMESTEP = 1;
	TRM_Count = 0;
	BLK_Count = 0;
	FCFS_Count = 0;
	SJF_Count = 0;
	RR_Count = 0;
	EDF_count = 0;
	ProcessesCount = 0;
	RunningCount = 0;
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
	TotalTRT = 0;
	BeforeDeadline = 0;
}

bool Scheduler::IO_requesthandling(PROCESS* RUN) {
	if (RUN == nullptr)
		return false;
	if (RUN->get_N() > 0 && RUN->get_countN() < RUN->get_N())
	{
		if (RUN->get_countsteps() == RUN->get_IO_R(RUN->get_countN()))
		{
			RUN->incrementcountN();
			Add_toblocklist(RUN); 
			RemoveFromRunning(RUN);
			RunningCount--;
			return true;
		}
	}
	return false;
}

bool Scheduler::Process_completion(PROCESS* RUN)
{
	if (RUN) {
		if (RUN->get_countsteps() >= RUN->get_CT())
		{
			Add_toterminatedlist(RUN);
			RunningCount--;
			RemoveFromRunning(RUN);
			return true;
		}
	}
	return false;
}

bool Scheduler::MIG_RR_SJF(PROCESS* run)
{
	if (check_is_SJF())
	{
		if ((run->get_CT() - run->get_countsteps()) < RTF)
		{
			increment_MigsDueRTF();
			FindShortestProcessor('S')->addToMyRdy(run);
			return true;
		}
		return false;
	}
}

bool Scheduler::MIG_FCFS_RR(PROCESS* run)
{
	if (check_is_RR())
	{
		if (!(run->get_isforked()))
		{

			if (get_WT_RR(run) > MaxW)
			{
				increment_MigsDueMax_W();
				FindShortestProcessor('R')->addToMyRdy(run);
					return true;
			}
		}
		return false;
	}
}


void Scheduler::SIMULATE()
{
	int RunMode = UIptr->SelectRunMode(); // Returns 1 for Interactive, 2 for Step-By-Step, 3 for Silent. 0 otherwise;
	LoadData(); //Step 1 Load Data from Input File
	
	while (!AllDone())
	{
		CheckNewArrivals(); //Step 3 Move processes with AT equaling Timestep to RDY Queue (Their time has come :) )
		Execute(); //Iterates over all processors and move Rdy processes to Running if possible
		AddToRunning();   //Iterates over all runnings of processors and add them to RUNNING array
		BLKtoRDY();
		WorkStealing();
		switch (RunMode)
		{
		case 1:
			Print('I');
			break;
		case 2:
			Print('B');
			break;
		default:
			break;
		}
		TIMESTEP++;
	}
	if(RunMode == 3)
		Print('S');
	CalculateStats(); // Calculate all statistics displayed in the output file
	SaveData(); // Produce the Output file
}

void Scheduler::CheckNewArrivals()
{
	if (NEW.isEmpty())
		return;
	PROCESS* temp;
	NEW.peek(temp);
	while (temp->get_AT() == TIMESTEP) 
	{
		NEW.dequeue(temp);
		FindShortestProcessor()->addToMyRdy(temp); // Shortest Processor RDY gets first elem in NEW queue
		if (NEW.isEmpty())
			return;
		NEW.peek(temp);
	}
}

void Scheduler::Execute()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i]->getCooldown() > 0)
			ListOfProcessors[i]->decrementCooldown();
		ListOfProcessors[i]->ScheduleAlgo();
	}
}

bool Scheduler::AllDone()
{
	
	return TRM_Count == LiveTotalProcesses;
}

void Scheduler::AddToRunning()
{
	for (int i = 0; i < totalProcessors; i++)  
	{
		if (ListOfProcessors[i]->getCurrentlyRunning())
			RUNNING[i] = ListOfProcessors[i]->getCurrentlyRunning()->get_PID();
	}
}

void Scheduler::WorkStealing()
{
	if (TIMESTEP % STL == 0) //every STL timestep
	{
		int LQF = ListOfProcessors[0]->getExpectedFinishTime();
		int SQF = ListOfProcessors[0]->getExpectedFinishTime();
		int indxProcessorOfSQF=0;
		int indxProcessorOfLQF=0;
		for (int i = 1;i < totalProcessors;i++) {
			int cur = ListOfProcessors[i]->getExpectedFinishTime();
			if (cur >= LQF) 
			{
				LQF = cur;
				indxProcessorOfLQF = i;
			}
			else if (cur <= SQF)
			{
				SQF = cur;
				indxProcessorOfSQF = i;
			}
		}
		if (LQF == 0)
		{
			return;
		}
		StealLimit = float((LQF - SQF))/ LQF;
		while (StealLimit > 0.4) 
		{
			if (!ListOfProcessors[indxProcessorOfLQF]->getRSIZE())
				return;
			PROCESS* topLQF = ListOfProcessors[indxProcessorOfLQF]->removeTopOfMyRDY();
		
			if (topLQF->get_isforked()) {
				PROCESS* temptopLQF = nullptr;
				if (ListOfProcessors[indxProcessorOfLQF]->getType() == "FCFS")
					PROCESS* temptopLQF = dynamic_cast<FCFS*> (ListOfProcessors[indxProcessorOfLQF])->find_first_nonforked_elemnt();
				else
					return;
				if (temptopLQF == nullptr) {
					ListOfProcessors[indxProcessorOfLQF]->addToMyRdy(topLQF);
					return;
				}
				else {
					topLQF = temptopLQF;
				}
			}
			ListOfProcessors[indxProcessorOfSQF]->addToMyRdy(topLQF);
			StealCount++;
			LQF = ListOfProcessors[indxProcessorOfLQF]->getExpectedFinishTime();
			SQF = ListOfProcessors[indxProcessorOfSQF]->getExpectedFinishTime();
			if (LQF == 0)
			{
				return;
			}
			StealLimit = float((LQF - SQF)) / LQF;
		}
	}
}

PROCESSOR* Scheduler::FindShortestProcessor(char x)
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
			if (ListOfProcessors[i]->getCooldown())
				continue;
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
			if (ListOfProcessors[i]->getCooldown())
				continue;
			if (ListOfProcessors[i]->getExpectedFinishTime() < shortestProcessor && ListOfProcessors[i]->getType() == "RR")
			{
				shortestProcessor = ListOfProcessors[i]->getExpectedFinishTime();
				shortestProcessorIndex = i;
			}
		}
		return ListOfProcessors[shortestProcessorIndex];
	}
	else if (x == 'F')
	{
		int shortestProcessor = INT_MAX; // Keeps track of the first FCFS processor to finish
		int shortestProcessorIndex = 0; // Index of the shortest FCFS
		for (int i = 1; i < FCFS_Count; i++)
		{
			if (ListOfProcessors[i]->getCooldown())
				continue;
			if (ListOfProcessors[i]->getExpectedFinishTime() < shortestProcessor && ListOfProcessors[i]->getType() == "FCFS")
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
		if (ListOfProcessors[i]->getCooldown())
			continue;
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
		if (tmp->get_IO_D(tmp->get_countN() - 1) > 0) //Checks for the given N(number of IO req), What is the remaining IO_D
			tmp->DecrementIOD(tmp->get_countN() - 1);
		else //checks if the processor IOD == 0, moves it to shortest RDY
		{
			BLK.dequeue(tmp);
			BLK_Count--;
			FindShortestProcessor()->addToMyRdy(tmp);
			if (BLK.peek(tmp)) {
				if (tmp->get_IO_D(tmp->get_countN() - 1) > 0) 
					tmp->DecrementIOD(tmp->get_countN() - 1);
			}
		}
	}
	
}

void Scheduler::CalculateStats()
{
	LinkedQueue<PROCESS*> tmpQ;  //Will store the processes temporarily till we put them back in TRM
	for (int i = 0; i < TRM_Count; i++)
	{
		PROCESS* temp;
		TRM.dequeue(temp);
		tmpQ.enqueue(temp);
		AvgWaitingTime += temp->get_WT();
		AvgResponseTime += temp->get_RT();
	}
	//Calculate Process Stats
	AvgWaitingTime /= TRM_Count;
	AvgResponseTime /= TRM_Count;
	AvgTRT = TotalTRT / TRM_Count;
	MigPercent_MaxW = (MigsDueMax_W / TRM_Count) * 100;
	MigPercent_RTF = (MigsDueRTF / TRM_Count) * 100;
	StealPercent = (float(StealCount) / TRM_Count) * 100;
	ForkPercent = (float(ForkedCount) / TRM_Count) * 100;
	KillPercent = (float(KilledCount) / TRM_Count) * 100;
	BeforeDeadlinePercent = (float(BeforeDeadline) / TRM_Count) * 100;
	while (!tmpQ.isEmpty())
	{
		PROCESS* temp;
		tmpQ.dequeue(temp);
		TRM.enqueue(temp);
	}
	//Calculate Processor Stats
	for (int i = 0; i < totalProcessors; i++)
	{
		ListOfProcessors[i]->CalculatePLoad(TotalTRT);
		ListOfProcessors[i]->CalculatePUtil();
	}
	
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

void Scheduler::increment_runningcount()
{
	RunningCount++;
}

void Scheduler::decrement_runningcount()
{
	RunningCount--;
}

void Scheduler::RemoveFromEverywhere(PROCESS* target)
{
	for (int i = 0; i < FCFS_Count; i++)
	{
		if (ListOfProcessors[i]->getCurrentlyRunning() == target)
		{
			ListOfProcessors[i]->KillRun();
			RemoveFromRunning(target);
			RunningCount--;
			return;
		}
		if (dynamic_cast<FCFS*>(ListOfProcessors[i])->isInMyRdy(target)) 
		{
			dynamic_cast<FCFS*>(ListOfProcessors[i])->RemoveFromMyRdy(target);
			return;
		}
	}
}

void Scheduler::RemoveFromRunning(PROCESS* target)
{
	for (int i = 0; i < totalProcessors; i++)
	{
		if (RUNNING[i] == target->get_PID())
			RUNNING[i] = 0;
	}
}

bool Scheduler::check_is_SJF()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i]->getType() == "SJF")
		{
			return true;
		}
	}
	return false;

}

bool Scheduler::check_is_RR()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i]->getType() == "RR")
		{
			return true;
		}
	}
	return false;
}

int Scheduler::get_WT_RR(PROCESS* running)
{
	return(TIMESTEP - (running->get_AT()) - (running->get_countsteps()));
}

void Scheduler::CreateNewProcess(PROCESS* parent)
{
	PROCESS* Baby = new PROCESS(TIMESTEP, ++LiveTotalProcesses, parent->get_CT() - parent->get_countsteps(), 0, 0);
	FindShortestProcessor('F')->addToMyRdy(Baby);
	Baby->set_isforked();
	ForkedCount++;
	if (parent->getChild1())
	{
		parent->setChild2(Baby);
		Baby->setParent(parent);
		return;
	}
	parent->setChild1(Baby);
	Baby->setParent(parent);
	return;
}

int Scheduler::GetTRT()
{
	return AvgTRT * TRM_Count;
}

void Scheduler::incrementBeforeDeadline()
{
	BeforeDeadline++;
}

int Scheduler::random()
{
	random_device rd;
	mt19937 gen(rd());

	// Define the distribution for the random number
	uniform_int_distribution<> dis(1, 100);

	// Generate and return the random number
	return dis(gen);
}

int Scheduler::getCoolTime() const
{
	return coolTime;
}

Scheduler::~Scheduler()
{
	for (int i = 0; i < totalProcessors; i++)
	{
		if (ListOfProcessors[i])
		{
			delete ListOfProcessors[i];
			ListOfProcessors[i] = nullptr;
		}
	}
}