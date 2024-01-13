/*
 * db.c -- Datenbank Bibliothek
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
#include <assert.h>
#include <time.h>
#include "db.h"

/* Warten von 1 bis 10000 Millisekunden (10 Sekunden) */
static void msleep(unsigned int ms)
{
	struct timespec ts;

	assert(ms > 0);
	assert(ms <= 10000);

	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms * 1000000) % 1000000000;
	nanosleep(&ts, NULL);
}

/* Pruefen, ob Datenbank vorhanden ist */
bool db_check(void)
{
	struct stat s;
	int err;

	err = stat(DB_FILENAME, &s);
	if (err == -1) {
		return false;
	}

	return S_ISREG(s.st_mode);
}

/* Datenbankeintrag lesen */
static void db_entry_read(unsigned int customer_id, struct db_entry *db_entry)
{
	int fd;
	off_t pos;
	ssize_t bytes;
	int err;

	assert(customer_id < DB_ENTRIES);
	assert(db_entry != NULL);

	fd = open(DB_FILENAME, O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	pos = lseek(fd, customer_id * sizeof(*db_entry), SEEK_SET);
	if (pos == (off_t)-1) {
		perror("lseek");
		exit(EXIT_FAILURE);
	}

	bytes = read(fd, db_entry, sizeof(*db_entry));
	if (bytes != sizeof(*db_entry)) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	err = close(fd);
	if (err == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}
}

/* Datenbankeintrag schreiben */
static void db_entry_write(unsigned int customer_id, struct db_entry *db_entry)
{
	int fd;
	off_t pos;
	ssize_t bytes;
	int err;

	assert(customer_id < DB_ENTRIES);
	assert(db_entry != NULL);

	fd = open(DB_FILENAME, O_WRONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	pos = lseek(fd, customer_id * sizeof(*db_entry), SEEK_SET);
	if (pos == (off_t)-1) {
		perror("lseek");
		exit(EXIT_FAILURE);
	}

	bytes = write(fd, db_entry, sizeof(*db_entry));
	if (bytes != sizeof(*db_entry)) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	err = close(fd);
	if (err == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}
}

/* Kontostand eines Datenbankeintrag aendern */
static void db_entry_change_balance(unsigned int customer_id, int amount)
{
	struct db_entry db_entry;

	assert(customer_id < DB_ENTRIES);
	assert(amount <= DB_MAX_TRANSFER);
	assert(amount >= -DB_MAX_TRANSFER);

	db_entry_read(customer_id, &db_entry);
	db_entry.balance += amount;
	db_entry_write(customer_id, &db_entry);
}

/*
 * Durchfuehrung einer Transaktion:
 * 1. Geld von Konto "from" abheben
 * 2. Zufaellige Wartezeit 300 bis 800 ms
 * 3. Geld auf Konto "to" einzahlen
 */
void db_money_transfer(unsigned int from, unsigned int to, unsigned int amount)
{
	assert(from < DB_ENTRIES);
	assert(to < DB_ENTRIES);
	assert(amount >= 1);
	assert(amount <= DB_MAX_TRANSFER);

	db_entry_change_balance(from, -amount);
	msleep(300 + rand() % 801);
	db_entry_change_balance(to, +amount);
}

/*
 * Bilanzsumme aller Konten berechnen
 */
int db_get_balance(void)
{
	struct db_entry db_entry;
	int sum = 0;

	for (unsigned int i = 0; i < DB_ENTRIES; ++i) {
		db_entry_read(i, &db_entry);
		sum += db_entry.balance;
	}

	return sum;
}
