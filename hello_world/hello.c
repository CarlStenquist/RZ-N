#include <stdio.h>

/* Added for WDT. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int func(int);

int main(int argc, char *argv[])
{
    int ret;
    
    setbuf(stdout, NULL); //Disable stdout buffering to immediately get text to terminal.
    
    /* Watchdog. */
	int fd_wdt, i = 0;

    printf("H e l l o...\n");
    ret = func(0);
    printf("Called func which returned %d.\n", ret);
    
    /* W A T C H D O G *
    * Open, then loop and service watchdog timer forever. */ 
    printf("Calling open watchdog.\n");
    fd_wdt = open("/dev/watchdog", O_WRONLY);
    if (fd_wdt == -1)
    {
		perror("Watchdog.");
		printf("Watchdog open FAILED.\n");
        exit(EXIT_FAILURE);
	}
    while (i < 5) 
    {
		ret = write(fd_wdt, "\0", 1);
		printf("Wrote to watchdog, %d\n", i);
        if (ret != 1)
        {
			printf("BAD write to watchdog.\n");
            ret = -1;
			break;
		}
		sleep(10);
        i ++;
	}
	printf("WARNING: Stopping writes to watchdog! System should reboot!!\n");
    close(fd_wdt);
	return ret;
}

int func(int x)
    {
        printf("W ");
        printf("o ");
        printf("r ");
        printf("l ");
        printf("d!\n");
        return 0;
    }
    /* file end */