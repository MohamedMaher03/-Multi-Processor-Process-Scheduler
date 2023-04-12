#include <iostream>
#include "Scheduler.h"
#include"Pair.h"
using namespace std;


int main()
{
	
	int n = 5;
	Pair* io;
	io = new Pair[n];
	(io+1)->setfirst(3);
	io->setsecond(4);
	cout << io[1].getfirst();
	cout << io[0].getsecond();
	
	Scheduler* Maestro = new Scheduler();
	Maestro->SIMULATE();
	return 0;
}