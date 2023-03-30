#include "PROCESS.h"
PROCESS::PROCESS(int ArrivalTime, int ID, int CPU_Time,
	int Number)
{
	AT = ArrivalTime;
	PID = ID;
	CT = CPU_Time;
	N = Number;
	if (!N)
	{
		IO_R = new int[N];
		IO_D = new int[N];
	}
	IsKilled = false;
	IsOrphan = false;

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

 bool PROCESS::get_IsKilled()
 {
	 return IsKilled;
 }

 bool PROCESS::get_IsParent()
 {
	 return IsParent;
 }

 void PROCESS::set_state(int x)
 {
	 if (x == 0)
		 state =_NEW;
	 if (x == 1)
		 state = _RDY;
	 if (x == 2)
		 state = _RUN;
	 if (x == 3)
		 state = _BLK;
	 if (x == 4)
		 state = _TRM;


 }

 int PROCESS::get_state()
 {
	 if (state == _NEW)
		 return 0;
	 if (state == _RDY)
		 return 1;
	 if (state == _RUN)
		 return 2;
	 if (state == _BLK)
		 return 3;
	 if (state == _TRM)
		 return 4;
 }

 