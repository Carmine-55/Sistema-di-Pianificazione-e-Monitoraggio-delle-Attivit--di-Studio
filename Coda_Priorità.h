//file.h 

#ifndef ATTIVITA_H
#define ATTIVITA_H

typedef struct coda_P *PCoda;

//prototipi

PCoda nuova_PC(void);
int vuota_PC(PCoda c);
Attività ottieni_max(PCoda c);
int cancella_max(PCoda c);
int inserisci(PCoda c, Attività nuovaAttività);

#endif