#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("filter.c\n");

	if(argc != 3)
	{
		printf("invalid count of arguments\n");
		return EXIT_FAILURE;
	}

	int pipes[2] = { 0, 0 };
	if(pipe(pipes) < 0)
		return EXIT_FAILURE;

	pid_t pid_ls = fork();
	if(!pid_ls)
	{
		dup2(pipes[1], STDOUT_FILENO);
		
		close(pipes[0]);
		close(pipes[1]);

		execlp("ls", "ls", "-la", argv[1]);
	}
	else if(pid_ls < 0)
	{
		close(pipes[0]);
		close(pipes[1]);

		return EXIT_FAILURE;
	}

	pid_t pid_grep = fork();
	if(!pid_grep)
	{
		dup2(pipes[0], STDIN_FILENO);

		close(pipes[0]);
		close(pipes[1]);

		fflush(NULL);
		execlp("grep", "grep", argv[2]);
	}
	else if(pid_ls < 0)
	{
		close(pipes[0]);
		close(pipes[1]);

		return EXIT_FAILURE;
	}

	close(pipes[0]);
	close(pipes[1]);

	waitpid(pid_ls, NULL, 0);
	waitpid(pid_grep, NULL, 0);

	return EXIT_SUCCESS;
}
