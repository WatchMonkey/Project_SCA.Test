#ifndef _hello_i_h_
#define _hello_i_h_

#include "hello_s.h"

class GreetingService_impl : virtual public POA_GreetingService
{
public:

   GreetingService_impl (CORBA::ORB_ptr orb EORB_ENV_ARGN);

   virtual CORBA::String greeting (const char* greetstr EORB_ENV_ARGN);
   virtual void shutdown (EORB_ENV_ARG1);

private:
   CORBA::ORB_ptr porb;
};

#endif
