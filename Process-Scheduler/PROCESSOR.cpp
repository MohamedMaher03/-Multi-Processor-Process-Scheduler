#include "PROCESSOR.h"
#include <iostream>

void PROCESSOR::PrintMyReady()
{
	RDY.printContents();
}

PROCESS* PROCESSOR::getCurrentlyRunning()
{
	return RUN;
}
