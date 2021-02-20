#include "hello.h"
#include "DataFile.h"
/*
 The GreetingService client example performs the minimal client tasks:

 1. initialize the ORB
 2. obtain a reference to an active GreetingService
 3. make a call on the GreetingService
*/

using namespace Data;

EORB_MAIN (client)
{
   EORB_DECLARE_ENV;

   EORB_IIOP_plugin ();

   EORB_TRY
   {
      CORBA::Object_var obj;
      CORBA::ORB_var orb;
      //GreetingService_var greeter;
	  ProcessedData_var process;
      CORBA::String_var returned;

      printf ("Hello portable client starting\n");

      // Initialize the ORB

      orb = CORBA::ORB_init (argc, argv EORB_ENV_VARN);
      EORB_CHECK_ENV;

      // Resolve server

      obj = orb->resolve_initial_references ("hello" EORB_ENV_VARN);
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

      orb->destroy (EORB_ENV_VAR1);
      EORB_CHECK_ENV;
   }
   EORB_CATCH (CORBA::Exception, exc)
   {
      printf ("Exception: %s\n", exc._rep_id ());
   }
   EORB_END_TRY

   printf ("Hello portable client complete\n");

   return 0;
}
