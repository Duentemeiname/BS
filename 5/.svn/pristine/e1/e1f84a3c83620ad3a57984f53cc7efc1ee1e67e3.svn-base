# Makefile Aufgabe "Signale und Pipes"

CFLAGS = -std=c11 -D_GNU_SOURCE -Og -g -W -Wall -Wno-unused-parameter \
         -Werror=implicit-function-declaration -Wfatal-errors -pthread

.PHONY: all clean distclean

all: db_new db_dump db_stress filter

db_new: db_new.c db.h
	$(CC) $(CFLAGS) -o $@ $<

db_dump: db_dump.c db.h
	$(CC) $(CFLAGS) -o $@ $<

db.o: db.c db.h
	$(CC) $(CFLAGS) -c -o $@ $<

db_stress: db_stress.c db.h db.o
	$(CC) $(CFLAGS) -o $@ $< db.o

filter: filter.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f db_new db_dump db.o db_stress filter

distclean: clean
	# Datenbank entfernen
	rm -f db.dat
