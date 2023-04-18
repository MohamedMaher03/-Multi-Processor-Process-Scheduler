#include <iostream>
#include "Scheduler.h"
using namespace std;


int main()
{
	Scheduler* Maestro = new Scheduler();
	Maestro->SIMULATE();
	delete Maestro;
	system("pause");
	return 0;	
}