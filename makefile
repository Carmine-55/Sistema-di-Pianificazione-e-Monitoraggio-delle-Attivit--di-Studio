coda_priorita.exe: coda_priorita.o attivita.o funzioni_file.o main.o 
	gcc -o coda_priorita.exe coda_priorita.o attivita.o funzioni_file.o main.o 

coda_priorita.o: coda_priorita.c 
	gcc -c coda_priorita.c 

attivita.o: attivita.c
	gcc -c attivita.c 

funzioni_file.o: funzioni_file.c 
	gcc -c funzioni_file.c 

main.o: main.c 
	gcc -c main.c 

clean:
	rm -f *.o coda_priorita.exe		