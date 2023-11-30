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

    printf("srcfilename: %s\n", srcfilename);
    printf("dstfilename: %s\n", dstfilename);

    int src = open(srcfilename, O_RDONLY);
    if (src == -1) {
        perror("Fehler beim Öffnen der Quelldatei");
        return EXIT_FAILURE;
    }

    int destination = open(dstfilename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    if (destination == -1) {
        perror("Fehler beim Öffnen der Zieldatei");
        close(src);
        return EXIT_FAILURE;
    }

    int file_size = lseek(src, 0, SEEK_END);
    if (file_size == (off_t)-1) {
        perror("Fehler beim Ermitteln der Dateigröße");
        close(src);
        close(destination);
        return EXIT_FAILURE;
    }

    char buffer[1];
    ssize_t bytesread = 0;
    off_t offset = file_size - 1;

    while (offset >= 0) {
        lseek(src, offset, SEEK_SET);
        bytesread = read(src, buffer, 1);
        if (bytesread == -1) {
            perror("Fehler beim Lesen der Daten");
            close(src);
            close(destination);
            return EXIT_FAILURE;
        }
        if (write(destination, buffer, 1) != 1) {
            perror("Fehler beim Schreiben in die Zieldatei");
            close(src);
            close(destination);
            return EXIT_FAILURE;
        }
        offset--;
    }

    close(src);
    close(destination);

    return EXIT_SUCCESS;
}
