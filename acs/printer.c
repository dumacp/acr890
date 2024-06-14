

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "acs_api.h"
#include "acs_errno.h"


void PrintTestPage()
{
	int Status;
	
	printer_setLineSpaceSM(30);
	printer_printStrSM("Advanced Card System Ltd");
	printer_printStrSM(" ");
	printer_printStrSM("    Sample Printing");
	printer_printStrSM(" ");
	printer_printStrSM("   2013/10/08 11:42:44");
	printer_printStrSM(" ");
	printer_printStrSM("Thank you for visiting our booth");
	printer_printStrSM(" ");

	

}

int main(int argc, char *argv[])
{
	int nRet;
	
	int interval = 3;
		
		if(argc == 1)
		{
			printf("Usage: %s\n",argv[0]);
		}
		else if(argc == 2)
		{
			
			printf("error parameter!\n");
			return 1;
		
		}
		else if(argc == 3)
		{
			printf("Usage: %s -i sec\n",argv[0]);
			if(strcmp(argv[1],"-i") == 0)
			{
				if(argv[2][0]>('0'-1) && argv[2][0]<('9'+1))
				{
					interval = atoi(argv[2]);
				}
				else
				{
					printf("error parameter!\n");
					return 1;
				}
			}
			else
			{
				printf("error parameter!\n");
				return 1;
			}
	  }
	  else
	  {
	  	printf("error parameter!\n");
				return 1;
	  }
	
	
	nRet=printer_open();	

	if(nRet<0)
	{
		printf("ACR890_Printer_Open erro %d\n",nRet);
		return ;
	}
	
	while(1)
	{
		
		PrintTestPage();
	
		if(interval == 0)
		{
			usleep(200);
		}
		else
		{
			sleep(interval);
		}		
	
	}
	
	printer_close();

	return 0;
}
