#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[])
{
	printf("Kind2 Start, PID: %d, PPID: %d\n", getpid(), getppid());

	volatile uint64_t counter = 0;
    time_t startTime = time(NULL);

    while (difftime(time(NULL), startTime) < 10) 
	{
        counter++;
        sleep(1);
    }

	return EXIT_SUCCESS;
}
