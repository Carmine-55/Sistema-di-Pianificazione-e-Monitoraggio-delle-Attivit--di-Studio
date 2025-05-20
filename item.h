#ifndef ITEM_H
#define ITEM_H

typedef enum {
     BASSA = 1,
     MEDIA = 2,
     ALTA = 3 
    } Priorita;

typedef enum {
     IN_CORSO,
     COMPLETATA,
     IN_RITARDO 
    } Stato;

typedef struct {
    char descrizione[100];
    char corso[50];
    char data_di_scadenza[11];
    int tempo_stimato;
    Priorita importanza;
    Stato stato;
} Attivita;

// Prototipi delle funzioni di gestione attività
void aggiungi_attivita(Attivita *a);
void modifica_attivita(Attivita *a);
int verifica_ritardo(const char *data_di_scadenza);
void mostra_attivita(const Attivita *a);

#endif
