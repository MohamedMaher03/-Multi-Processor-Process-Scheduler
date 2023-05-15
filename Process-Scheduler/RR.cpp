 #include "RR.h"
#include "Scheduler.h"

RR::RR(Scheduler* sc):PROCESSOR(sc)
{
	STATE = 0;
	RUN = nullptr;
	TYPE = "RR";
	RSIZE = 0;
	PLoad = 0;
	PUtil = 0;
	TotalBusyTime = 0;
}

RR::~RR()
{
}

void RR::ScheduleAlgo()
{
	if (!RUN)
		TotalIdleTime++;
	else
		TotalBusyTime++;

	if (!RUN && RDY.isEmpty())
		return;
		if (!STATE)//the processor is IDLE
		{
			PROCESS* front;
			if(RDY.dequeue(front))
			{
				RUN = front;
				STATE = 1;
				RUN->set_starttime(SchedPtr->get_TIMESTEP());
				RSIZE--;
				ExpectedFinishTime -= front->get_CT();
				RUN->incrementCountsteps(1);
			}
			
		}
		else {
			if (SchedPtr->Process_completion(RUN))
			{
				RUN = nullptr;
				STATE = 0;
			}
			else if (SchedPtr->IO_requesthandling(RUN))
			{
				RUN = nullptr;
				STATE = 0;
			}
			else {
				if (RUN->get_countsteps() < SchedPtr->getTimeSlice())
				{
					if ((RUN->get_CT() - RUN->get_countsteps()) < SchedPtr->getRTF())
					{
						RUN->incrementCountsteps(1);
					}
					else
					{
						//migrate to SJF
					}
				}
				else
				{
					if ((RUN->get_CT() - RUN->get_countsteps()) > SchedPtr->getRTF())
					{
						//migrate to SJF
					}
					else
					{
						RDY.enqueue(RUN);
						RSIZE++;
						ExpectedFinishTime += RUN->get_CT();
					}

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

bool RR::PromoteProcess()
{
	if (!STATE && !RDY.isEmpty())// the processor is IDLE
	{
		PROCESS* toberun;
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
