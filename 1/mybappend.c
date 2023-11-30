#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    printf("Haenge an Datei byteweise an ...\n");

    if (argc != 3) {
        fprintf(stderr, "Programm falsch ausgeführt!: %s Quelldatei Zieldatei\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *srcfilename = argv[1];
    const char *dstfilename = argv[2];

    if (access(srcfilename, F_OK) == -1) {
        perror("Die Quelldatei existiert nicht");
        return EXIT_FAILURE;
    }

    int src = open(srcfilename, O_RDONLY);
    if (src == -1) {
        perror("Fehler beim Öffnen der Quelldatei");
        return EXIT_FAILURE;
    }

    if (access(dstfilename, F_OK) == -1) {
        perror("Die Zieldatei existiert nicht");
        close(src);
        return EXIT_FAILURE;
    }

    int destination = open(dstfilename, O_WRONLY | O_APPEND);
    if (destination == -1) {
        perror("Fehler beim Öffnen der Zieldatei");
        close(src);
        return EXIT_FAILURE;
    }

    char buffer[1];
    ssize_t bytesRead;

    while (bytesRead = read(src, buffer,1)) {
        if (write(destination, buffer, bytesRead) != bytesRead) {
            perror("Fehler beim Schreiben in die Zieldatei");
            close(src);
            close(destination);
            return EXIT_FAILURE;
        }
    }

    close(src);
    close(destination);

    printf("Datei erfolgreich angehängt.\n");
    return EXIT_SUCCESS;
}
