#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "acs_api.h"

int main(int argc, char *argv[])
{

	int i;
	int ret;
	struct led_state state;
		
	while(1)
	{
		if(argc>1)
		{
			printf("Usage: %s off|on\n",argv[0]);
			if(strcmp(argv[1],"off") == 0)
			{
				state.OnOffBlinkState = (enum led_blink_state)0;
				for(i=0; i<4; i++)
				{
					led_set_state((enum led_id)i,state);
				}
				break;
			}
			else if(strcmp(argv[1],"on") == 0)
			{
				state.OnOffBlinkState = (enum led_blink_state)1;
				for(i=0; i<4; i++)
				{
					led_set_state((enum led_id)i,state);
				}
				break;
			}
		}
		
		/*state.OnOffBlinkState = (enum led_blink_state)0;
		for(i=0; i<4; i++)
		{
			led_set_state((enum led_id)i,state);
		}*/

		for(i=0; i<4; i++)
		{
			state.OnOffBlinkState = (enum led_blink_state)2;
			state.OnTimeMs = 50;
			state.OffTimeMs = 50;
			led_set_state((enum led_id)i,state);

			//sleep(1);

			state.OnOffBlinkState = (enum led_blink_state)0;
			led_set_state((enum led_id)i,state);
		}

		//usleep(500000);

		/*state.OnOffBlinkState = (enum led_blink_state)1;
		for(i=0; i<4; i++)
		{
			led_set_state((enum led_id)i,state);
		}*/
	
	}

	return 0;
}

