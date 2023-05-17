#include "PROCESS.h"
using namespace std;

PROCESS::PROCESS(int ArrivalTime, int ID, int CPU_Time, int deadline, int Number)
{
	AT = ArrivalTime;
	PID = ID;
	CT = CPU_Time;
	Deadline = deadline;
	N = Number;
	lastCT = 0;
	Countsteps = 0;//added
	CountN = 0;    //added
	StartTime = -1; //added
	totalIoD = 0;
	if (N)
	{
		IO = new Pair[N]; // array of pairs 
						  //IO.first->IO-R
						  //IO.second->IO-D
	}
	IsKilled = false;
	isforked = false;
	Child1 = nullptr;
	Child2 = nullptr;
	set_state("NEW");	
	RT = -1;
	WT = 0;
}
PROCESS::~PROCESS()
{
	if(N)
		delete [] IO;
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
 int PROCESS:: getlastCT() const {
	 return lastCT;

 }
 void PROCESS:: set_IsKilled()
 {
	 IsKilled = 1;
 }

 void PROCESS::set_isforked()
 {
	 isforked = 1;
 }

 int PROCESS::get_PID() const
 {
	 return PID;
 }

 int PROCESS::get_AT() const
 {
	 return AT;
 }

 int PROCESS::get_RT() const
 {
	 return RT;
 }

 int PROCESS::get_CT() const
 {
	 return CT;
 }

 int PROCESS::get_TT() const
 {
	 return TT;
 }

 int PROCESS::get_TRT() const
 {
	 return TRT;
 }

 int PROCESS::get_WT() const
 {
	 return WT;
 }
 int PROCESS::get_deadline() const {
	 return Deadline;
 }

 bool PROCESS::get_isforked()
 {
	 return isforked;
 }

 void PROCESS::set_starttime(int t)
 {
	 if(StartTime==-1)  //if not initialize before
	 StartTime = t;
 }
 void PROCESS::setlastCT(int num) {
	 lastCT = num;
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

 int PROCESS::get_N() const
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

 void PROCESS::set_IO(int IO_R, int IO_D, int ind)
 {
	 (IO + ind)->setfirst(IO_R);  
	 (IO + ind)->setsecond(IO_D);
 }

 int PROCESS::get_IO_R(int indx) const
 {
	 return (IO + indx)->getfirst();
 }

 int PROCESS::get_IO_D(int indx) const
 {
	 return (IO + indx)->getsecond();
 }
 bool PROCESS::get_IsKilled() const
 {
	 return IsKilled;
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

 /*bool PROCESS::operator>=(PROCESS&another_process)
 {
	 if (CT >= another_process.get_CT())
		 return true;
	 return false;
 }

 bool PROCESS::operator<=(PROCESS&another_process)
 {
	 if (CT <= another_process.get_CT())
		 return true;
	 return false;
 }*/

 int PROCESS::get_totalIoD() const
 {
	 return totalIoD;
 }

 void PROCESS::setTotalIO_D(int x)
 {
	 totalIoD = x;
 }

 void PROCESS::setParent(PROCESS* pr)
 {
	 Parent = pr;
 }

 void PROCESS::setChild1(PROCESS* ch)
 {
	 Child1 = ch;
 }

 void PROCESS::setChild2(PROCESS* ch)
 {
	 Child2 = ch;
 }

 PROCESS* PROCESS::getParent() const
 {
	 return Parent;
 }

 PROCESS* PROCESS::getChild1() const
 {
	 return Child1;
 }

 PROCESS* PROCESS::getChild2() const
 {
	 return Child2;
 }

 void PROCESS::DecrementIOD(int indx)
 {
	 int IO_D = (IO + indx)->getsecond();
	 IO_D--;
	 (IO + indx)->setsecond(IO_D);
 }

 void PROCESS::SetTRT(int x)
 {
	 TRT = x;
 }

 void PROCESS::setWT(int x)
 {
	 WT = x;
 }

 