#pragma once
#include<string>
using namespace std;
class PROCESS
{

	int PID;
	int AT;
	int RT;
	int CT;
	int TT;
	int TRT;
	int WT;
	int  N;
	int StartTime; //added 
	int Countsteps; //added
	int CountN; //added
	int* IO_R;
	int* IO_D;
	bool IsKilled;
	bool IsParent;
	bool IsOrphan;
	enum STATES;
	STATES state;
public:

	PROCESS(int ArrivalTime, int ID, int CPU_Time,	int Number);
	void set_RT(int response);
	void set_TT(int termination);
	void set_TRT(int termination, int ArrivalTime);
	void set_WT(int termination, int ArrivalTime, int CPU_Time);
	void set_IsKilled();
	void set_IsParent(bool Parent);
	void set_IsOrphan();
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	void set_starttime(int t); //added
	int get_starttime();	   //added
	int get_countsteps();	   //added
	void incrementCountsteps();//added
	int get_countN();			//added
	void incrementcountN();     //added
	int get_N();                //added
	bool get_IsOrphan();
	void set_IO_R(int val, int index);
	void set_IO_D(int val, int index);
	int get_IO_R(int index);    //added
	bool get_IsKilled();
	bool get_IsParent();
	void set_state(string x);
	string get_state();
	bool operator >= (PROCESS another_process);
	bool operator <= (PROCESS another_process);
	~PROCESS();


};
