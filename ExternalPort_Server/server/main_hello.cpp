#include "hello_i.h"
#include "DataFile_i.h"
/*
 The GreetingServer example performs the minimal server tasks:

 1. initialize the ORB
 2. create an object implementation instance (servant)
 3. activate it in a POA
 4. create an object reference
 5. publish that reference so that a client can use it
 6. wait for requests
*/

using namespace POA_Data;

int main_back_two (int argc, char ** argv)
{
   EORB_DECLARE_ENV;
   //GreetingService_impl * servant = 0;
   externport_impl* servant = 0x0;

   EORB_IIOP_plugin ();
   EORB::Plugin::POA::add ();

   EORB_Stdio_plugin ();
   EORB_File_plugin ();

   EORB_TRY
   {
      PortableServer::ObjectId_var oid;
      CORBA::Object_var obj;
      PortableServer::POA_var poa;
      CORBA::ORB_var orb;

      printf ("Hello portable server starting\n");

      // Initialize the ORB

      //orb = CORBA::ORB_init (argc, argv EORB_ENV_VARN);
	  int temp_middle_int = 0x0;
	  char** temp_middle_str = NULL;
	  orb = CORBA::ORB_init (temp_middle_int, temp_middle_str EORB_ENV_VARN);
      EORB_CHECK_ENV;

      // Get the RootPOA

      obj = orb->resolve_initial_references ("RootPOA" EORB_ENV_VARN);
      EORB_CHECK_ENV;
      
      poa = PortableServer::POA::_narrow (obj EORB_ENV_VARN);
      EORB_CHECK_ENV;

	  /*
      // Initialize the servant

      servant = new GreetingService_impl (orb EORB_ENV_VARN);
      EORB_CHECK_ENV;

      oid = poa->activate_object (servant EORB_ENV_VARN);
      EORB_CHECK_ENV;

      // Register reference

      obj = poa->servant_to_reference (servant EORB_ENV_VARN);
      EORB_CHECK_ENV;

      orb->register_initial_reference ("hello", obj EORB_ENV_VARN);
      EORB_CHECK_ENV;
	  */


	  servant = new externport_impl (orb EORB_ENV_VARN);
	  EORB_CHECK_ENV;

	  oid = poa->activate_object (servant EORB_ENV_VARN);
	  EORB_CHECK_ENV;

	  // Register reference

	  obj = poa->servant_to_reference (servant EORB_ENV_VARN);
	  EORB_CHECK_ENV;

	  char* temp_str = orb->object_to_string(obj);
	  printf("==<Info>the string:%s\n",temp_str);

	  orb->register_initial_reference ("externDataPort", obj EORB_ENV_VARN);
	  EORB_CHECK_ENV;
      // Listen for requests
 
      orb->run (EORB_ENV_VAR1);
      EORB_CHECK_ENV;

      // Clean up

      orb->destroy (EORB_ENV_VAR1);
      EORB_CHECK_ENV;
   }
   EORB_CATCH (CORBA::Exception, exc)
   {
      printf ("Exception: %s\n", exc._rep_id ());
   }
   EORB_END_TRY

   delete servant;

   printf ("Hello portable server complete\n");

   return 0;
}

