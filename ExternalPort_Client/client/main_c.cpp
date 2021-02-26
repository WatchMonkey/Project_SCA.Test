#include "hello.h"
#include "DataFile.h"

#include <Windows.h>
#include <iostream>
#include <cstdlib>
/*
 The GreetingService client example performs the minimal client tasks:

 1. initialize the ORB
 2. obtain a reference to an active GreetingService
 3. make a call on the GreetingService
*/

using namespace Data;


CORBA::ORB_var orb;


DWORD WINAPI MyThreadProc1(LPVOID lpParameter);

EORB_MAIN (client)
{
	HANDLE handle1;
	handle1 = CreateThread(NULL,0x0,MyThreadProc1,0x0,CREATE_SUSPENDED,0x0);
	

   EORB_DECLARE_ENV;

   EORB_IIOP_plugin ();

   EORB_TRY
   {
      CORBA::Object_var obj;
      CORBA::ORB_var orb;
      //GreetingService_var greeter;
	  ProcessedData_var process;
	  ProcessedData_var process_extern;
      CORBA::String_var returned;

	  CORBA::ORB::ObjectIdList_ptr temp_idlist;

      printf ("Hello portable client starting\n");

	  int temp_middle = argc - 0x1;
	  char** temp_middle_str = (char**)malloc(sizeof(char*) * temp_middle);
	  for(int temp_i = 0x0;temp_i < argc;++temp_i){
		  printf("==<info>the argv[%d]:%s\n",temp_i,argv[temp_i]);
		  if(temp_i == 0x0)continue;
		  temp_middle_str[temp_i - 0x1] = strdup(argv[temp_i]);
		  printf("==<info>the argv_new[%d]:%s\n",temp_i - 0x1,temp_middle_str[temp_i - 0x1]);
	  }

	  temp_middle_str[0x0] = "-ORBInitRef";
	  temp_middle_str[0x1] = "dOut=corbaloc:iiop:192.168.0.138:12900/dOut";
	  //temp_middle_str[0x1] = "dOut=IOR:010000001b00000049444c3a446174612f50726f636573736564446174613a312e30000000000000";

	  process_extern = ProcessedData::_duplicate(process EORB_ENV_VARN);

      // Initialize the ORB
	  orb = CORBA::ORB_init (temp_middle, temp_middle_str EORB_ENV_VARN);
	  //char** temp_middle = NULL;
	  //int temp_middle_int = 0x0;
      //orb = CORBA::ORB_init (temp_middle_int, temp_middle EORB_ENV_VARN);
      EORB_CHECK_ENV;


	  //list orb all object
	  temp_idlist = orb->list_initial_services();
	  for(int temp_i = 0x0;temp_i < temp_idlist->length();++temp_i)
	  {
			printf("==<Info>the init object index %d:%s\n",temp_i,(*temp_idlist)[temp_i].in());
	  }


      // Resolve server

      obj = orb->resolve_initial_references ("dOut" EORB_ENV_VARN);
      EORB_CHECK_ENV;

      // Narrow the object to a GreetingServer

      //greeter = GreetingService::_narrow (obj EORB_ENV_VARN);
	  process = ProcessedData::_narrow (obj EORB_ENV_VARN);
      EORB_CHECK_ENV;

      // Call to server
	  CF::OctetSeq temp_seq;
	  temp_seq.length(0x20);
	  for(int temp_i = 0x0;temp_i < 0x20;++temp_i){
		  temp_seq[temp_i] = 0xA0 + temp_i;
	  }
      //greeter->greeting ("World" EORB_ENV_VARN);
	  process->pushProcessedData(temp_seq EORB_ENV_VARN);
      EORB_CHECK_ENV;

      //printf ("%s\n", returned.in ());

      // Shutdown the server

      //greeter->shutdown (EORB_ENV_VAR1);
      //EORB_CHECK_ENV;

      // Clean up
	  bool temp_bool = CORBA::is_nil(orb);
	  CORBA::Object_var obj_nil = CORBA_OBJECT_NIL;
	  bool temp_bool_nil = CORBA::is_nil(obj_nil);
	  if(temp_bool){
		  return 0x0;
	  }

	  orb->shutdown(true EORB_ENV_VARN);
	  EORB_CHECK_ENV;
	  orb->destroy(EORB_ENV_VAR1);
	  EORB_CHECK_ENV;
   }
   EORB_CATCH (CORBA::Exception, exc)
   {
      printf ("Exception: %s\n", exc._rep_id ());
   }
   EORB_END_TRY

   printf ("Hello portable client complete\n");
   
   CloseHandle(handle1);

   return 0;
} 





DWORD WINAPI MyThreadProc1(LPVOID lpParameter)
{
	cout<<"The MyThreadProc1 is Running !"<<endl;

	/*
	orb->shutdown(true EORB_ENV_VARN);
	EORB_CHECK_ENV;
	orb->destroy(EORB_ENV_VAR1);
	EORB_CHECK_ENV;
	*/
	std::cout<<"the orb destroy"<<std::endl;

	return 0;
}