#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        fprintf(stderr, "Verwendung: %s <Dateiname> <Länge>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dateiname = argv[1];
    int neue_laenge = atoll(argv[2]); 

    int datei_fd = open(dateiname, O_RDWR);

    if (datei_fd == -1) {

        datei_fd = open(dateiname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
        if (datei_fd == -1) {
            perror("Fehler beim Erstellen der Datei");
            return EXIT_FAILURE;
        }
    }

    if (ftruncate(datei_fd, neue_laenge) == -1) {
        perror("Fehler beim Setzen der Dateilänge");
        close(datei_fd);
        return EXIT_FAILURE;
    }

    close(datei_fd);
    printf("Die Datei %s wurde auf %d Bytes vergrößert.\n", dateiname, neue_laenge);

    return EXIT_SUCCESS;
}
