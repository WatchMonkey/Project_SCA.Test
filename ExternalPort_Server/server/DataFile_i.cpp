#include "DataFile_i.h"

namespace POA_Data
{
	externport_impl::externport_impl (CORBA::ORB_ptr orb EORB_ENV_ARGN)
	{
		porb = orb;
	}

	void externport_impl::pushProcessedData
		(
		const CF::OctetSeq& pkt 
		EORB_ENV_ARGN
		)
	{
		printf("==<Info>externport_impl get the data\n");
		int temp_length = pkt.length();
		printf("==<Info>externport_impl get data length:%d\n",temp_length);
	}

}
