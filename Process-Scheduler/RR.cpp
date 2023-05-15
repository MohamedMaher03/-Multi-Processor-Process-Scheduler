 #include "RR.h"
#include "Scheduler.h"

RR::RR(Scheduler* sc):PROCESSOR(sc)
{
	STATE = 0;
	RUN = nullptr;
	TYPE = "RR";
	RSIZE = 0;
	
}

RR::~RR()
{
}

void RR::ScheduleAlgo()
{
	if (!RUN && RDY.isEmpty())
		return;
		if (!(RDY.isEmpty())&&(!RUN))//the processor is IDLE
		{
			count_RR = 0;
			PROCESS* front;
			if(RDY.dequeue(front))
			{
				RUN = front;
				STATE = 1;
				RUN->set_starttime(SchedPtr->get_TIMESTEP());
				RSIZE--;
				ExpectedFinishTime -= front->get_CT();
				SchedPtr->increment_runningcount();
				
			}
			
		}
		
			
		
			if (SchedPtr->Process_completion(RUN))
			{
				RUN = nullptr;
				STATE = 0;
				return;
			}
			if (SchedPtr->IO_requesthandling(RUN))
			{
				RUN = nullptr;
				STATE = 0;
				return;
			}

		
		if (RUN)
		{
			/*if ((SchedPtr->MIG_RR_SJF(RUN)))
			{
				RUN = nullptr;
			}
			else*/
			{
				if (count_RR < SchedPtr->getTimeSlice())
				{
					RUN->incrementCountsteps(1);
					count_RR++;
				}
				else
				{
					RDY.enqueue(RUN);
					ExpectedFinishTime += RUN->get_CT();
					SchedPtr->decrement_runningcount();
					RUN = NULL;
					RSIZE++;
					
					

				}
			}
		}
				
			
		
		
}

void RR::PrintMyReady()
{
	RDY.printContents();
}

void RR::addToMyRdy(PROCESS* TMP)
{
	RDY.enqueue(TMP);
	ExpectedFinishTime += TMP->get_CT();
	RSIZE++;
}

PROCESS* RR::removeTopOfMyRDY()
{
	PROCESS* top=nullptr;
	if (RDY.dequeue(top)) {
		RSIZE--;
		ExpectedFinishTime -= top->get_CT();
	}
	return top;
}

bool RR::PromoteProcess(int x)
{
	if (!STATE && !RDY.isEmpty())// the processor is IDLE
	{
		PROCESS* toberun;
		//If RDY.peek() exists I want to check if the timestep is equal AT, if this is the case return false
		if(RDY.peek(toberun))
		if (x == toberun->get_AT())
			return false;
		if (RDY.dequeue(toberun))
		{
			RUN = toberun;
			STATE = 1;
			RSIZE--;
			ExpectedFinishTime -= toberun->get_CT();
			return true;
		}
	}
	return false;
}
