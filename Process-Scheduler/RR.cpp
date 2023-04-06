#include "RR.h"
#include"PROCESS.h"


RR::RR()
{
	RUN = NULL;
	type = "RR";
}

void RR::ScheduleAlgo()
{

	PROCESS* front;

	while (!(RDY.isEmpty()))
	{
		if (!RUN)
		{
			RUN = front;
			RUN->set_starttime(sch_ptr->get_TIMESTEP());
			if ((RUN->get_CT()-RUN->get_countsteps()) > sch_ptr->getRTF())
			{
				RUN->incrementCountsteps(sch_ptr->getTimeSlice());
				sch_ptr->increase_TIMESTEP_RR();
				if (RDY.enqueue(RUN))
					RUN = NULL;
			}
			else
			{
				//send to scheduler to migrate it to FCFS

			}

		}
	}



}

int RR::getRSIZE()
{
	return RDY.getlength();
}


string RR::gettype()
{
	return type;
}
