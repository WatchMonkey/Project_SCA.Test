#include "hello_i.h"
#include "DataFile_i.h"
#include "eOrb/EORB/Plugin/Current.h"
#include "eOrb/EORB/Plugin/Any.h"
#include "eOrb/services/full/CosNaming.h"
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

int main_back (int argc, char ** argv)
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

	int temp_argc = 0x3;
	char** temp_argv = (char**)calloc(sizeof(char*),temp_argc);

	EORB_TRY
	{
		PortableServer::ObjectId_var oid;
		CORBA::Object_var obj;
		PortableServer::POA_var poa;
		CORBA::ORB_var orb;
		CosNaming::NamingContext_var name;
		CosNaming::NamingContext_var domain_ctx;

		printf ("Hello portable server starting\n");

		// Initialize the ORB
		temp_argv[0x0] = _pgmptr;
		temp_argv[0x1] = "-ORBInitRef";
		temp_argv[0x2] = "NameService=corbaloc:iiop:1.2@192.168.0.242:2809/NameService";
		//temp_argv[0x2] = "Filter=IOR:010000002f00000049444c3a4d616e61676564436f6d704d6f64756c652f4d616e61676564436f6d70496e746572666163653a312e30000003000000044f415440000000010102000e0000003139322e3136382e302e323432003fe02000000001921800654f52421aca8e530100000005454f5242000000040000000100000000000000004f41544c000000010102001a0000002f746d702f75696f702e706c6e785f61726d2e6b73384a64730000002000000001921800654f52421aca8e530100000005454f52420000000400000001000000000000000000000040000000010102000e0000003139322e3136382e302e3234320035a52000000001921800654f52421aca8e530100000005454f5242000000040000000100000000000000";
		orb = CORBA::ORB_init(temp_argc,temp_argv );
		//EORB_CHECK_ENV;

		// Get the RootPOA
		obj = orb->resolve_initial_references ("RootPOA" );
		//EORB_CHECK_ENV;
		poa = PortableServer::POA::_narrow (obj );
		//EORB_CHECK_ENV;

		
		//get nameservice
		obj = orb->resolve_initial_references("NameService" );
		//EORB_CHECK_ENV;
		name = CosNaming::NamingContext::_narrow(obj );
		//EORB_CHECK_ENV;
		/*if(CORBA::is_nil(name) == true){
			EORB_THROW_RETURN()
		}*/

		
		// get domain
		CosNaming::NameComponent domain_com;
		CosNaming::Name domain(0x1);
		char* temp_name_one = "myDomain";
		domain.length(0x1);
		domain_com.id = temp_name_one;
		domain_com.kind = "";
		domain[0x0] = domain_com;
		obj = name->resolve(domain );
		//EORB_CHECK_ENV;
		domain_ctx = CosNaming::NamingContext::_narrow(obj);
		//EORB_CHECK_ENV;
		

		//instance servant
		servant = new externport_impl (orb );
		//EORB_CHECK_ENV;
		//active servant
		oid = poa->activate_object (servant );
		//EORB_CHECK_ENV;

		// Register reference
		obj = poa->servant_to_reference (servant );
		//EORB_CHECK_ENV;
		char* temp_str = orb->object_to_string(obj);
		printf("==<Info>the string:%s\n",temp_str);
		
		CosNaming::NameComponent port_servant;
		char* temp_out = strdup("dataOut");
		port_servant.id = temp_out;
		port_servant.kind = (const char*)"";
		CosNaming::Name port(0x1);
		port.length(0x1);
		port[0x0] = port_servant;
		domain_ctx->bind(port,obj );
		//EORB_CHECK_ENV;
		/*
		orb->register_initial_reference ("dataOut", obj );
		//EORB_CHECK_ENV;
		*/
		// Listen for requests
		orb->run ();
		//EORB_CHECK_ENV;
		// Clean up
		orb->destroy ();
		//EORB_CHECK_ENV;
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

