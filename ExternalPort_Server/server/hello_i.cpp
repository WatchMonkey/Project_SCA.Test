#include "hello_i.h"

GreetingService_impl::GreetingService_impl (CORBA::ORB_ptr orb EORB_ENV_ARGN)
{
   porb = orb;
}

CORBA::String GreetingService_impl::greeting
(
   const char * greetstr
   EORB_ENV_ARGN
)
{
   char hellostr[200];

   strcpy (hellostr, "Hello ");
   strcat (hellostr, greetstr);
   strcat (hellostr, "!");

   printf ("Saying hello to %s\n", greetstr);

   return CORBA::string_dup (hellostr);
}

void GreetingService_impl::shutdown (EORB_ENV_ARG1)
{
   porb->shutdown (0 EORB_ENV_VARN);
}
