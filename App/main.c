#include "rsystem.h" 

int main(void)
{
 	BSP_Init();
	while(1)
	{	
      
	    MainKeytask();
	    Getdatatask();
 	    
		  VoltageSampleTask();
		
		
	}

}

