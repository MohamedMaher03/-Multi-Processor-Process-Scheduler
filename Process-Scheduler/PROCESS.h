#pragma once
class PROCESS
{
public:
	int PID;
	int AT;
	int RT;
	int CT;
	int TT;
	int TRT;
	int WT;
	int IO_R;
	int IO_D;
	int NO_OF_IO;
	bool IsKilled;
	bool IsParent;


	PROCESS(int ArrivalTime, int ID, int CPU_Time,
		int N, int Request_IO, int Duration_IO);

	void set_RT(int response);
	void set_TT(int termination);
	void set_TRT(int termination, int ArrivalTime);
	void set_WT(int termination, int ArrivalTime, int CPU_Time);
	void set_IsKilled(bool killed);
	void set_IsParent(bool Parent);
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	int get_IO_R();
	int get_IO_D();
	bool get_IsKilled();
	bool get_IsParent();


};
