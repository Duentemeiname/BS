#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Programm falsch ausgeführt!: %s Quelldatei Zieldatei Puffergröße\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *srcfilename = argv[1];
    const char *dstfilename = argv[2];
    size_t buffersize = atoi(argv[3]);

    printf("srcfilename: %s\n", srcfilename);
    printf("dstfilename: %s\n", dstfilename);
    printf("Puffergröße: %zu\n", buffersize);

    struct stat src_stat;
    if (stat(srcfilename, &src_stat) == -1) {
        perror("Fehler beim Abrufen der Dateiinformationen");
        return EXIT_FAILURE;
    }

    if (!S_ISREG(src_stat.st_mode)) {
        fprintf(stderr, "Quelldatei ist keine reguläre Datei.\n");
        return EXIT_FAILURE;
    }

    int src = open(srcfilename, O_RDONLY);
    if (src == -1) {
        perror("Fehler beim Öffnen der Quelldatei");
        return EXIT_FAILURE;
    }

    int destination = open(dstfilename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (destination == -1) {
        perror("Fehler beim Öffnen der Zieldatei");
        close(src);
        return EXIT_FAILURE;
    }

    char buffer[buffersize];
    ssize_t bytesRead;

    while ((bytesRead = read(src, buffer, buffersize)) > 0) {
        if (write(destination, buffer, bytesRead) != bytesRead) {
            perror("Fehler beim Schreiben in die Zieldatei");
            close(src);
            close(destination);
            return EXIT_FAILURE;
        }
    }

    close(src);
    close(destination);

    if (chmod(dstfilename, src_stat.st_mode) == -1) {
        perror("Fehler beim Festlegen der Zugriffsrechte für die Zieldatei");
        return EXIT_FAILURE;
    }

    printf("Datei erfolgreich kopiert: %s zu %s\n", srcfilename, dstfilename);

    return EXIT_SUCCESS;
}
