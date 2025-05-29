test_app.exe: test_progetto.o test_main.o attivita.o coda_priorita.o funzioni_file.o
	gcc -o test_app.exe test_progetto.o test_main.o attivita.o coda_priorita.o funzioni_file.o

test_progetto.o: test_progetto.c test_progetto.h attivita.h coda_priorita.h funzioni_file.h
	gcc -c test_progetto.c

test_main.o: test_main.c test_progetto.h
	gcc -c test_main.c

attivita.o: attivita.c attivita.h
	gcc -c attivita.c

coda_priorita.o: coda_priorita.c coda_priorita.h attivita.h
	gcc -c coda_priorita.c

funzioni_file.o: funzioni_file.c funzioni_file.h coda_priorita.h
	gcc -c funzioni_file.c

clean:
	rm -f *.o test_app.exe