#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "db.h"

#include <unistd.h>
#include <signal.h>

/*
 * Durchfuehrung einer Transaktion:
 * 1. Zufaelligen Betrag von einem zufaelligen Konto abheben
 * 2. Diesen Betrag auf ein zufaelliges Konto wieder einzahlen
 */

void random_transaction(void)
{
	unsigned int from_customer = rand() % DB_ENTRIES;
	unsigned int to_customer = rand() % DB_ENTRIES;
	int amount = 1 + rand() % DB_MAX_TRANSFER;

	db_money_transfer(from_customer, to_customer, amount);
}

void sigint_handler(int num) 
{
	printf("\n[Abbruch] Bilanzsumme: %d\n", db_get_balance());
	fflush(stdout);

	exit(EXIT_SUCCESS);
}

void sigusr1_handler(int num) 
{
	printf("\n[Info] Bilanzsumme: %d\n", db_get_balance());
	fflush(stdout);
}

void sigalrm_handler(int num) 
{
	printf("\n[*] Bilanzsumme: %d\n", db_get_balance());
	fflush(stdout);

	alarm(5);
}


int main(int argc, char *argv[])
{
	printf("Datenbank Stresstest\n");
	printf("pid: %d\n", getpid());

	if (!db_check()) {
		printf("Datenbank nicht gefunden!\n");
		printf("Legen Sie eine Datenbank mit $ ./db_new an!\n");
		exit(EXIT_FAILURE);
	}

	/* Stresstest: 1000 zufaellige Transaktionen */
	sigset_t sigset;

	struct sigaction sa_int;
	struct sigaction sa_usr1;
	struct sigaction sa_alrm;

	sigemptyset(&sigset);

	sigaddset(&sigset, SIGINT);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGALRM);

	sa_int.sa_handler = sigint_handler;
	sa_usr1.sa_handler = sigusr1_handler;
	sa_alrm.sa_handler = sigalrm_handler;

	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGUSR1, &sa_usr1, NULL);
	sigaction(SIGALRM, &sa_alrm, NULL);

	alarm(5);

	for (size_t i = 0; i < 1000; ++i) {
		sigprocmask(SIG_BLOCK, &sigset, NULL);
		random_transaction();
		sigprocmask(SIG_UNBLOCK, &sigset, NULL);
	}

	printf("Bilanz am Ende: %d\n", db_get_balance());

	return EXIT_SUCCESS;
}
