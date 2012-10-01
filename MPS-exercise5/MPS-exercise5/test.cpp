#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cstdlib>
#include <iostream>

int main(void)
{

	int led;
	int key;
	char buf[20];
	while(true)
	{
		key = open("/dev/bootkey", O_RDONLY);
		
		read(key, buf, 20);
		close(key);
		usleep(1000000);
			
		if(buf[1]=='1')
		{
			led = open("/dev/sysled4", O_WRONLY);
			write(led, "1", 1);
			close(led);
		}
		else
		{
			led = open("/dev/sysled4", O_WRONLY);
			write(led, "0", 1);
			close(led);
		}
		
		printf("FRA BUFF %a \n", buf);
		usleep(1000000);	

	}
	  
	return 0;
}



