#include "DataFile_i.h"


#define LOG_DATA_ENABLE 0x1

namespace POA_Data
{
	externport_impl::externport_impl (CORBA::ORB_ptr orb EORB_ENV_ARGN)
	{
		porb = orb;
		Count = 0x0;
		Count_Byte = 0x0;
		buffer_data = (CORBA::ULong*)calloc(sizeof(CORBA::ULong),0x1000);
	}

	void externport_impl::pushProcessedData
		(
		const CF::OctetSeq& pkt 
		EORB_ENV_ARGN
		)
	{
		Count++;
		int temp_length = pkt.length();
		Count_Byte += temp_length;
		int temp_array_size = (temp_length / 0x4) + 0x1;

		//printf the receive data
#if(LOG_DATA_ENABLE == 0x1)
		printf("==<Info>[%d]externport_impl get data length Uint:%d,Byte:%d Data:\n",Count,temp_array_size,temp_length);
		//log data
		CORBA::ULong temp_data_index = 0x0;
		memset(buffer_data,0x0,temp_length * sizeof(CORBA::ULong));
		for(int temp_i = 0x0;temp_i < temp_length;++temp_i)
		{
			CORBA::ULong temp_middle = 0x0;
			temp_middle |= pkt[temp_i * 0x4] << 24;
			temp_middle |= pkt[temp_i * 0x4 + 0X1] << 16;
			temp_middle |= pkt[temp_i * 0x4 + 0X2] << 8;
			temp_middle |= pkt[temp_i * 0x4 + 0X3];
			//record array
			buffer_data[temp_data_index] = temp_middle;
			temp_data_index++;
		}

		//show receive data from port
		int temp_j = 0x0;
		for(;temp_j < temp_array_size;++temp_j)
		{
			printf(" %08x ",buffer_data[temp_j]);
			if(((temp_j + 0x1)% 10) == 0x0)printf("\n");
		}
		if((temp_j % 10) != 0x0)printf("\n");
#else
		//if((Count % 200) != 0x0)return;
		printf("==<Info>[%d]externport_impl get data length Uint:%d,Byte:%d AllByteCount:%d\n",Count,temp_array_size,temp_length,Count_Byte);
#endif
	}
}
