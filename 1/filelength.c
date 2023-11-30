#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Verwendung: %s <Dateiname>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dateiname = argv[1];
    FILE *datei = fopen(dateiname, "rb");

    if (datei == NULL) {
        perror("Fehler beim Öffnen der Datei");
        return EXIT_FAILURE;
    }

    fseek(datei, 0, SEEK_END);
    int datei_laenge = ftell(datei);

    if (datei_laenge == -1) {
        perror("Fehler beim Ermitteln der Dateilänge");
        fclose(datei);
        return EXIT_FAILURE;
    }

    printf("Die Länge der Datei %s beträgt %d Bytes\n", dateiname, datei_laenge);

    fclose(datei);
    return EXIT_SUCCESS;
}

