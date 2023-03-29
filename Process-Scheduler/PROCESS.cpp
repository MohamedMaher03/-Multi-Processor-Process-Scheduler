#include "PROCESS.h"
PROCESS::PROCESS(int ArrivalTime, int ID, int CPU_Time,
	int N, int Request_IO, int Duration_IO)
{
	AT = ArrivalTime;
	PID = ID;
	CT = CPU_Time;
	NO_OF_IO = N;
	IO_R = Request_IO;
	IO_D = Duration_IO;

}

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

 void PROCESS:: set_IsKilled(bool killed)
 {
	 IsKilled = killed;
 }

 void PROCESS::set_IsParent(bool parent)
 {
	 IsParent = parent;
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

 int PROCESS::get_IO_R()
 {
	 return IO_R;
 }

 int PROCESS:: get_IO_D()
 {
	 return IO_D;
 }

 bool PROCESS::get_IsKilled()
 {
	 return IsKilled;
 }

 bool PROCESS::get_IsParent()
 {
	 return IsParent;
 }
