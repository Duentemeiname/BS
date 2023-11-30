#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
            fprintf(stderr, "Programm falsch ausgeführt!: %s Quelldatei Zieldatei\n", argv[0]);
            return EXIT_FAILURE;
        }
    
	printf("Hallo, Betriebssysteme-Praktikum!\n");
	printf("Kopiere der Datei rückwärts ...\n");
    
        const char *srcfilename = argv[1];
        const char *dstfilename = argv[2];

        printf("srcfilename: %s\n", srcfilename);
        printf("dstfilename: %s\n", dstfilename);

        if (access(srcfilename, F_OK) == -1) {
            perror("Die Quelldatei existiert nicht");
            return EXIT_FAILURE;
        }
    
        int src = open(srcfilename, O_RDONLY);
        if (!src) {
            perror("Fehler beim Öffnen der Quelldatei");
            return EXIT_FAILURE;
        }

        int destination = open(dstfilename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (!destination) {
            perror("Fehler beim Öffnen der Zieldatei");
            close(src);
            return EXIT_FAILURE;
        }

        char* buffer[1];
        ssize_t bytesRead;

        while (bytesRead = read(src, buffer, 1)) {
            if (write(destination, buffer, bytesRead) != bytesRead) {
                perror("Fehler beim Schreiben in die Zieldatei");
                close(src);
                close(destination);
                return EXIT_FAILURE;
            }
        }

        close(src);
        close(destination);

        printf("Datei erfolgreich kopiert: %s zu %s\n", srcfilename, dstfilename);

        return EXIT_SUCCESS;
}