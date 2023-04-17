#include <iostream>
#include "Scheduler.h"
using namespace std;


int main()
{
	/*
	PROCESS* f = new PROCESS(1, 2, 3, 4);
	PROCESS* s = new PROCESS(1, 1, 3, 4);
	LinkedPriorityQueue<PROCESS*>RDY;
	PROCESS* RUN;
	RDY.enqueue(f);
	RDY.enqueue(s);
	RDY.printContents();
	RDY.dequeue(s);
	RUN = s;
	cout << endl<<RUN->get_CT();
	/*
	int n = 5;
	Pair* io;
	io = new Pair[n];
	(io+1)->setfirst(3);
	io->setsecond(4);
	cout << io[1].getfirst();
	cout << io[0].getsecond();
	*/
	Scheduler* Maestro = new Scheduler();
	Maestro->SIMULATE();
	delete Maestro;
	return 0;
	
}