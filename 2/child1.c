#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("Kind1 Start, PID: %d, PPID: %d\n", getpid(), getppid());
	sleep(10);
	printf("Kind_1 Ende\n");
	return EXIT_SUCCESS;
}
