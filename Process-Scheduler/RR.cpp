 #include "RR.h"
#include "Scheduler.h"

RR::RR()
{
	TYPE = "RR";
	RUN = nullptr;
}

void RR::ScheduleAlgo()
{

	//PROCESS* front;

	//while (!(RDY.isEmpty()))
	//{
	//	if (!STATE)//the processor is IDLE
	//	{

	//		RUN = front;
	//		RUN->set_starttime(sch_ptr->get_TIMESTEP());
	//		if ((RUN->get_CT() - RUN->get_countsteps()) > sch_ptr->getRTF())
	//		{
	//			while ((sch_ptr->get_TIMESTEP() - RUN->get_starttime()))
	//				RUN->incrementCountsteps(sch_ptr->getTimeSlice());

	//			if (RDY.enqueue(RUN))
	//				RUN = NULL;
	//		}
	//		else
	//		{
	//			//send to scheduler to migrate it to FCFS

	//		}

	//	}
	//}



}

void RR::PrintMyReady()
{
	RDY.printContents();
}

void RR::addToMyRdy(PROCESS* TMP)
{
	RDY.enqueue(TMP);
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
			return true;
		}
	}
	return false;
}
