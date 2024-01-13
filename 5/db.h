/*
 * db.h -- Interface Datenbank Bibliothek
 *
 * azuepke, 2019-10-09: initial
 */

#ifndef DB_H
#define DB_H

/** Dateiname der Datenbank */
#define DB_FILENAME "db.dat"

/** Anzahl der Eintraege in der DB */
#define DB_ENTRIES 100

/** Bilanzbetrag in der Datenbank ueber alle Datensaetze */
#define DB_BALANCE 10000

/** Maximaler Betrag einer Ueberweisung */
#define DB_MAX_TRANSFER 1000

/**
 * Das Datenbankformat:
 * - die Datenbank ist in Spalten und Zeilen organisiert
 * - eine Zeile entspricht einem Datensatz
 * - jede Zeile besteht aus folgenden Spalten:
 *   - char name[28];    Name des Kunden
 *   - int balance;      Der Kontostand eines Kunden.
 */
struct db_entry {
	char name[28];
	int balance;
};

/**
 * Pruefen, ob Datenbank vorhanden und eine regulaere Datei ist.
 * Die Funktion gibt in diesem Fall true zurueck.
 */
bool db_check(void);

/**
 * Durchfuehrung einer Transaktion:
 * Ein Betrag zwischen 1 bis DB_MAX_TRANSFER Geldeinheiten
 * wird von dem Konto "from" abgehoben und auf dem Konto "to" eingezahlt.
 * Die Konten "from" und "to" muessen gueltige Konten-IDs
 * im Bereich 0 .. DB_ENTRIES-1 sein.
 */
void db_money_transfer(unsigned int from, unsigned int to, unsigned int amount);

/**
 * Bilanzsumme aller Konten berechnen.
 * Die Funktion gibt die Summe aller Kontostaende zurueck.
 */
int db_get_balance(void);

#endif
