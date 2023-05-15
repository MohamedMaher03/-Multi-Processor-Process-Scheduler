#pragma once
#include<string>
#include"Pair.h"
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
	int Deadline;
	int StartTime; //the time at which process first enter in any processor
	int Countsteps;// counter for the time steps that process take till now 
	int CountN;	   //number of times process use IO till now 
	bool IsKilled;
	bool isforked; //if process is forked return true
	Pair* IO;      //IO.first->IO-R   ,  IO.second->IO-D
	enum STATES;
	STATES state;
	int totalIoD;
	int RTF;
	int MaxW;
	PROCESS* Parent;
	PROCESS* Child1;
	PROCESS* Child2;
public:
	PROCESS(int ArrivalTime, int ID, int CPU_Time, int deadline, int Number);
	void set_RT(int response);
	void set_TT(int termination);
	void set_TRT(int termination, int ArrivalTime);
	void set_WT(int termination, int ArrivalTime, int CPU_Time);
	void set_IsKilled();
	void set_isforked();
	int get_PID() const;
	int get_AT() const;
	int get_RT() const;
	int get_CT() const;
	int get_TT() const;
	int get_TRT() const;
	int get_WT() const;
	bool get_isforked();
	void set_starttime(int t); 
	int get_starttime();	   
	int get_countsteps();	   
	void incrementCountsteps(int step);
	int get_countN();			
	void incrementcountN();   
	int get_N() const;             
	void set_IO(int IO_R, int IO_D, int ind);
	bool get_IsKilled() const;
	int get_IO_R(int indx) const;
	int get_IO_D(int) const;
	void set_state(string x);
	string get_state();
	int get_totalIoD() const;
	int calculateTotalIO_D();
	void setParent(PROCESS*);
	void setChild1(PROCESS*);
	void setChild2(PROCESS*);
	PROCESS* getParent() const;
	PROCESS* getChild1() const;
	PROCESS* getChild2() const;
	void DecrementIOD(int);
	void SetTRT(int);
	void setWT(int);
	~PROCESS();


};
