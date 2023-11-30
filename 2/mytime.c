#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Aufruf mit zu wenigen Argumenten!");
        exit(EXIT_FAILURE);
    }

    printf("mytime ...\n");

    struct timespec start_time, end_time;

    if (clock_gettime(CLOCK_MONOTONIC, &start_time) == -1) 
    {
        perror("Fehler beim Erfassen der Startzeit");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fehler beim Erzeugen des Kindprozesses");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execve(argv[1], &argv[1], NULL);
        perror("Fehler beim Ausführen des Kindprozesses");
        exit(EXIT_FAILURE);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("Fehler beim Warten auf den Kindprozess");
        exit(EXIT_FAILURE);
    }

    if (clock_gettime(CLOCK_MONOTONIC, &end_time) == -1) 
    {
        perror("Fehler beim Erfassen der Endzeit");
        exit(EXIT_FAILURE);
    }

    uint64_t ausfuehrungszeit = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
                              (end_time.tv_nsec - start_time.tv_nsec) / 1000;

    printf("PID: %d\n", pid);
    printf("Status: %d\n", WEXITSTATUS(status));
    printf("Ausführungszeit in Mikrosekunden: %lu \n", ausfuehrungszeit);

    return EXIT_SUCCESS;
}
