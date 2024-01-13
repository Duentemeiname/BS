/*
 * db_new.c -- Datenbank neu erstellen
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
#include <time.h>
#include "db.h"

#define countof(x) ((sizeof(x)/sizeof((x)[1])))

const char* honorifics[] = {
	"Meister",
	"Grossmeister",
	"Altmeister",
	"Prinz",
	"Koenig",
};

/* inspiriert von: http://www.larisweb.de/tools/namen_gen_zwerg.php */
const char* firstnames[] = {
	"Berg",
	"Stein",
	"Gruben",
	"Feuer",
	"Wasser",
	"Donner",
	"Sturm",
	"Eisen",
	"Stahl",
	"Gold",
	"Silber",
	"Kupfer",
	"Kristall",
	"Rot",
	"Braun",
	"Schwarz",
	"Weiss",
	"Alt",
	"Neu",
};

const char* lastnames[] = {
	"sucher",
	"graeber",
	"werfer",
	"schreiber",
	"graeber",
	"schmied",
	"freund",
	"schatz",
	"fund",
	"mann",
	"bart",
	"faust",
	"hand",
	"fuss",
	"auge",
	"herz",
	"blut",
	"feld",
	"lob",
	"glanz",
};

int main(int argc, char *argv[])
{
	printf("Lege neue Datenbank an: ");

	/* zufaellige Namen generieren */
	srand(getpid() ^ time(NULL));

	/* leere Datenbank */
	struct db_entry db[DB_ENTRIES] = { 0 };

	/* Zufaellig generierte Namen der Kunden */
	for (size_t i = 0; i < DB_ENTRIES; ++i) {
		if ((rand() % 4) == 0) {
			/* 25% mit Ehrenwuerde */
			snprintf(db[i].name, sizeof(db[i].name), "%s %s%s",
			         honorifics[rand() % countof(honorifics)],
			         firstnames[rand() % countof(firstnames)],
			         lastnames[rand() % countof(lastnames)]);
		} else {
			/* 75% ohne Ehrenwuerde */
			snprintf(db[i].name, sizeof(db[i].name), "%s%s",
			         firstnames[rand() % countof(firstnames)],
			         lastnames[rand() % countof(lastnames)]);
		}
	}

	/* Verteile die urspruengliche Bilanzsumme ueber alle Eintraege */
	unsigned int remaining_money = DB_BALANCE;
	while (remaining_money > 0) {
		unsigned int money;
		if (remaining_money > 100) {
			money = (rand() % (remaining_money / 20)) + 1;
		} else {
			money = (rand() % remaining_money) + 1;
		}
		db[rand() % DB_ENTRIES].balance += money;
		remaining_money -= money;
	}

	/* Datenkbank in Datei schreiben */
	int fd = open(DB_FILENAME, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if (fd == -1) {
		perror("open");
		return EXIT_FAILURE;
	}

	ssize_t bytes = write(fd, db, sizeof(db));
	if (bytes != sizeof(db)) {
		perror("write");
		return EXIT_FAILURE;
	}

	int err = close(fd);
	if (err == -1) {
		perror("close");
		return EXIT_FAILURE;
	}

	printf("OK\n");

	return EXIT_SUCCESS;
}
