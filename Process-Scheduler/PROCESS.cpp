#include "PROCESS.h"
PROCESS::PROCESS(int ArrivalTime, int ID, int CPU_Time,
	int Number)
{
	AT = ArrivalTime;
	PID = ID;
	CT = CPU_Time;
	N = Number;
	Countsteps = 0;//added
	CountN = 0;    //added
	StartTime = -1; //added
	if (!N)
	{
		IO_R = new int[N];
		IO_D = new int[N];
	}
	IsKilled = false;
	IsOrphan = false;
	state = _NEW;

}
PROCESS::~PROCESS()
{

}

enum PROCESS::STATES
{
	_NEW,
	_RDY,
	_RUN,
	_BLK,
	_TRM
};

 void PROCESS::set_RT(int response)
{
	 RT = response;
}
 
 void PROCESS::set_TT(int termination)
 {
	 TT = termination;
 }

 void PROCESS::set_TRT(int termination, int ArrivalTime)
 {
	 TRT = termination - ArrivalTime;
 }

 void PROCESS:: set_WT(int termination, int ArrivalTime, int CPU_Time)
 {
	 WT = termination - ArrivalTime - CPU_Time;
 }

 void PROCESS:: set_IsKilled()
 {
	 IsKilled = 1;
 }

 void PROCESS::set_IsParent(bool parent)
 {
	 IsParent = parent;
 }

 void PROCESS::set_IsOrphan()
 {
	 IsOrphan = true;
 }


 int PROCESS::get_PID()
 {
	 return PID;
 }

 int PROCESS::get_AT()
 {
	 return AT;
 }

 int PROCESS::get_RT()
 {
	 return RT;
 }

 int PROCESS::get_CT()
 {
	 return CT;
 }

 int PROCESS::get_TT()
 {
	 return TT;
 }

 int PROCESS::get_TRT()
 {
	 return TRT;
 }

 int PROCESS::get_WT()
 {
	 return WT;
 }

 void PROCESS::set_starttime(int t)
 {
	 if(StartTime==-1)  //if not initialize before
	 StartTime = t;
 }

 void PROCESS::incrementCountsteps(int step)
 {
	 Countsteps+=step;
 }

 int PROCESS::get_countN()
 {
	 return CountN;
 }

 void PROCESS::incrementcountN()
 {
	 CountN++;
 }

 int PROCESS::get_N()
 {
	 return N;
 }

 int PROCESS::get_starttime()
 {
	 return StartTime;
 }

 int PROCESS::get_countsteps()
 {
	 return Countsteps;
 }

 bool PROCESS::get_IsOrphan()
 {
	 return IsOrphan;
 }

 void PROCESS::set_IO_R(int val, int index)
 {
	 IO_R[index] = val;
 }

 void PROCESS::set_IO_D(int val, int index)
 {
	 IO_D[index] = val;
 }

 int PROCESS::get_IO_R(int index)
 {
	 return IO_R[index];
 }



 bool PROCESS::get_IsKilled()
 {
	 return IsKilled;
 }

 bool PROCESS::get_IsParent()
 {
	 return IsParent;
 }

 void PROCESS::set_state(string x)
 {
	 if (x == "NEW")
		 state =_NEW;
	 if (x == "READY")
		 state = _RDY;
	 if (x == "RUN")
		 state = _RUN;
	 if (x == "BLOCK")
		 state = _BLK;
	 if (x == "TERMINATE")
		 state = _TRM;
 }

 string PROCESS::get_state()
 {
	 switch (state)
	 {
	 case _NEW:
		 return "NEW";
	 case _RDY:
		 return "READY";
	 case _RUN:
		 return "RUN";
	 case _BLK:
		 return "BLOCKED";
	 case _TRM:
		 return "TERMINATED";
	 default:
		 return "NONE";
	 }
 }

 bool PROCESS::operator>=(PROCESS another_process)
 {
	 if (TT >= another_process.TT)
		 return true;
	 return false;
 }

 bool PROCESS::operator<=(PROCESS another_process)
 {
	 if (TT <= another_process.TT)
		 return true;
	 return false;
 }

 