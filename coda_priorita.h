#ifndef CODA_PRIORITA_H
#define CODA_PRIORITA_H

#include "item.h" // Importa la struttura Attivita e le funzioni di gestione attività

#define MAX_HEAP 50

typedef struct {
    Attivita vet[MAX_HEAP]; // Array di attività memorizzate nell'heap
    int num_elementi; // Numero attuale di elementi nella coda
} CodaPriorita, *PCoda;

// Prototipi delle funzioni per gestire la coda a priorità
PCoda nuova_PC(void);
int vuota_PC(PCoda c);
int inserisci(PCoda c, Attivita nuovaAttivita);
Attivita ottieni_max(PCoda c);
void mostra_progresso(PCoda c);
void genera_report_settimanale(PCoda c);
void elimina_attivita(PCoda c);
void completa_un_attivita(PCoda c);

#endif
