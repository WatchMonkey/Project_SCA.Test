#include "hello_i.h"
#include "DataFile_i.h"
#include "eOrb/EORB/Plugin/Current.h"
#include "eOrb/EORB/Plugin/Any.h"
#include "eOrb/EORB/Plugin/RTPOA.h"
#include "eOrb/EORB/Plugin/RTORB.h"
#include "eOrb/services/full/CosNaming.h"
#include "eOrb/EORB/NamingService.h"
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

int main (int argc, char ** argv)
{
	EORB_DECLARE_ENV;
	externport_impl* servant = 0x0;

	//plugin
	EORB::Plugin::Current::add();
	EORB::Plugin::Any::add();
	EORB::Plugin::POA::add();
	EORB_IIOP_plugin ();

	EORB_Stdio_plugin ();
	EORB_File_plugin ();
//	EORB::Plugin::RTORB::add ();
//	EORB::Plugin::RTPOA::add ();
	EORB_DIOP_plugin ();  // UDP transport
	//EORB_UIOP_plugin ();  // UN transport

	int temp_argc = 0x3;
	char** temp_argv = (char**)calloc(sizeof(char*),temp_argc);

	EORB::NamingService::Config config;
	config.qosMaxContexts = 11;
	config.qosPersistent = 0;
	CORBA::ORB::ObjectIdList_ptr temp_idlist;

	EORB_TRY
	{
		PortableServer::ObjectId_var oid;
		CORBA::Object_var obj;
		PortableServer::POA_var poa;
		CORBA::ORB_var orb;
		CosNaming::NamingContext_var name_ctx;
		CosNaming::NamingContext_var domain_ctx;

		printf ("Hello portable server starting\n");

		// Initialize the ORB
		temp_argv[0x0] = _pgmptr;
		//temp_argv[0x1] = "-ORBPOAEndpoints";
		temp_argv[0x1] = "-ORBListenEndpoints";
		//temp_argv[0x2] = "dOut:iiop:192.168.0.127:12900";
		temp_argv[0x2] = "iiop:192.168.0.239:12900";
		//temp_argv[0x2] = "Filter=IOR:010000002f00000049444c3a4d616e61676564436f6d704d6f64756c652f4d616e61676564436f6d70496e746572666163653a312e30000003000000044f415440000000010102000e0000003139322e3136382e302e323432003fe02000000001921800654f52421aca8e530100000005454f5242000000040000000100000000000000004f41544c000000010102001a0000002f746d702f75696f702e706c6e785f61726d2e6b73384a64730000002000000001921800654f52421aca8e530100000005454f52420000000400000001000000000000000000000040000000010102000e0000003139322e3136382e302e3234320035a52000000001921800654f52421aca8e530100000005454f5242000000040000000100000000000000";
		orb = CORBA::ORB_init(temp_argc,temp_argv EORB_ENV_VARN);
		EORB_CHECK_ENV;

		//list obj
		temp_idlist = orb->list_initial_services(EORB_ENV_VAR1);
		for(int temp_i = 0x0;temp_i < temp_idlist->length();++temp_i){
			printf("==<Info>the init object index %d:%s\n",temp_i,(*temp_idlist)[temp_i].in());
		}

		// Get the RootPOA
		obj = orb->resolve_initial_references ("RootPOA" EORB_ENV_VARN);
		EORB_CHECK_ENV;
		poa = PortableServer::POA::_narrow (obj EORB_ENV_VARN);
		EORB_CHECK_ENV;

		//instance servant
		servant = new externport_impl (orb EORB_ENV_VARN);
		EORB_CHECK_ENV;
		//active servant
		oid = poa->activate_object (servant EORB_ENV_VARN);
		EORB_CHECK_ENV;
		Data::ProcessedData_ptr server = servant->_this(EORB_ENV_VAR1);
		EORB_CHECK_ENV;
		obj = poa->servant_to_reference(servant EORB_ENV_VARN);
		EORB_CHECK_ENV;

		//init nameservice
		name_ctx = EORB::NamingService::init(orb,NULL,config EORB_ENV_VARN);
		EORB_CHECK_ENV;
		
		//register
		orb->register_initial_reference("NameService",name_ctx EORB_ENV_VARN);
		EORB_CHECK_ENV;
		orb->register_initial_reference("dOut",obj EORB_ENV_VARN);
		EORB_CHECK_ENV;

		//list obj
		temp_idlist = orb->list_initial_services(EORB_ENV_VAR1);
		for(int temp_i = 0x0;temp_i < temp_idlist->length();++temp_i){
			printf("==<Info>the init object index %d:%s\n",temp_i,(*temp_idlist)[temp_i].in());
		}

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
	free(temp_argv);

	printf ("Hello portable server complete\n");

	return 0;
}

