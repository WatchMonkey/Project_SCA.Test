#include "DataFile_s.h"

namespace POA_Data
{
	class externport_impl : virtual public ProcessedData
	{
	public:

		externport_impl (CORBA::ORB_ptr orb EORB_ENV_ARGN);
		virtual ~externport_impl(){
			free(buffer_data);
			printf("==<Info>[%d]externport_impl destruct,AllByteCount:%d\n",Count,Count_Byte);
		}
		virtual void pushProcessedData (const CF::OctetSeq& pkt EORB_ENV_ARGN);

	private:
		CORBA::ORB_ptr porb;
		int Count;
		CORBA::ULong* buffer_data;
		UINT Count_Byte;
	};
}