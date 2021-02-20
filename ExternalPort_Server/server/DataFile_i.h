#include "DataFile_s.h"

namespace POA_Data
{
	class externport_impl : virtual public ProcessedData
	{
	public:

		externport_impl (CORBA::ORB_ptr orb EORB_ENV_ARGN);

		virtual void pushProcessedData (const CF::OctetSeq& pkt EORB_ENV_ARGN);

	private:
		CORBA::ORB_ptr porb;
	};
}