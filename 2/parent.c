#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("Elternprozess ...\n");

    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 == -1) {
        perror("Fehler beim Erzeugen des ersten Kindprozesses");
        exit(EXIT_FAILURE);
    } 
	else if (pid1 == 0) 
	{
        execl("./child1", "child1", (char *)NULL);
        perror("Fehler bei execl für Kind1");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();

    if (pid2 == -1) {
        perror("Fehler beim Erzeugen des zweiten Kindprozesses");
        exit(EXIT_FAILURE);
    } 
	else if (pid2 == 0) 
	{
        execl("./child2", "child2", (char *)NULL);
        perror("Fehler bei execl für Kind2");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 15; i++) 
	{
        sleep(1);
        int systemDateResult = system("date");
        int systemPsResult = system("ps f");

        (void)systemDateResult;
        (void)systemPsResult;
    }

    if (waitpid(pid1, NULL, 0) != -1) 
	{
        printf("Erster Kindprozess beendet, PID: %d, PPID: %d\n", getpid(), getppid());
        int systemDateResult = system("date");
        (void)systemDateResult;
    } 
	else 
	{
        perror("Fehler beim Warten auf das Beenden des ersten Kindprozesses");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid2, NULL, 0) != -1) 
	{
        printf("Zweiter Kindprozess beendet, PID: %d, PPID: %d\n", getpid(), getppid());
        int systemDateResult = system("date");
        (void)systemDateResult;
    } 
	else 
	{
        perror("Fehler beim Warten auf das Beenden des zweiten Kindprozesses");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
