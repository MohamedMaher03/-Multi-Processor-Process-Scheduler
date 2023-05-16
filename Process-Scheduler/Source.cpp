#include <iostream>
#include "Scheduler.h"
using namespace std;


int main()
{
	Scheduler* Maestro = new Scheduler();
	Maestro->SIMULATE();
	delete Maestro;
	return 0;
	
}