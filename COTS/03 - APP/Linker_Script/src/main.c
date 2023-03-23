


#include <stdint.h>

__attribute__ ((section(".my_section"),used))
uint32_t MyVarNotInit ;
uint32_t MyVarInit = 100 ;
const uint32_t MyVarConst = 100 ;

extern unsigned int _my_section_start;

extern void print_var(const uint32_t * var);


int Yousef(int argc, char* argv[])
{
	static uint32_t Local_a;
	static uint32_t Local_b = 90;
	static const uint32_t Local_c = 900;

  while (1)
    {
	  print_var(&MyVarConst);
	  print_var(&Local_c);

	  _my_section_start++;
	  MyVarInit++;
	  MyVarNotInit++;
	  Local_a++;
	  Local_b++;
	  if(MyVarInit >= MyVarConst || MyVarNotInit >= MyVarConst)
	  {
		  MyVarInit = 0;
		  MyVarNotInit = 0;
	  }
	  if(Local_a >= Local_c || Local_b > Local_c)
	  {
		  Local_a = 0;
		  Local_b = 0;

	  }
       // Add your code here.
    }
}

