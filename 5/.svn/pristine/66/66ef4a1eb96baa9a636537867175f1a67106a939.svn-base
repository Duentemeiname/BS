/*
 * db_dump.c -- Datenbank ausgeben
 *
 * azuepke, 2019-10-09: initial
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "db.h"

int main(int argc, char *argv[])
{
	printf("*** Datenbank Dump ***\n");

	int fd = open(DB_FILENAME, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	/* Datenbank zeilenweise aus Datei auslesen */
	size_t entry = 0;
	int sum = 0;
	while (true) {
		struct db_entry db_entry;
		ssize_t bytes = read(fd, &db_entry, sizeof(db_entry));
		if (bytes == 0) {
			break;
		}
		if (bytes != sizeof(db_entry)) {
			perror("read, database corrupted?");
			return EXIT_FAILURE;
		}

		printf("%3zd: '%-32s' %7d\n", entry, db_entry.name, db_entry.balance);

		sum += db_entry.balance;
		++entry;
	}

	int err = close(fd);
	if (err == -1) {
		perror("close");
		return EXIT_FAILURE;
	}

	printf("*** Insgesamt %zd Eintraege, Bilanzsumme %d ***\n", entry, sum);

	return EXIT_SUCCESS;
}
