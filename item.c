#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "item.h"

// Aggiunta di un'attività
void aggiungi_attivita(Attivita *a) {
    printf("*** INSERISCI DESCRIZIONE ***: ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = 0;

    printf("*** INSERISCI IL NOME DEL CORSO ***: ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = 0;

    printf("*** INSERISCI LA DATA DI SCADENZA (GG/MM/AAAA) ***: ");
    fgets(a->data_di_scadenza, sizeof(a->data_di_scadenza), stdin);
    a->data_di_scadenza[strcspn(a->data_di_scadenza, "\n")] = 0;

    printf("*** INSERISCI IL TEMPO STIMATO (ORE) ***:");
    scanf("%d", &a->tempo_stimato);
    getchar();

    int priorita;
    printf("*** INSERISCI PRIORITA' (BASSA = 1, MEDIA = 2, ALTA = 3) ***: ");
    scanf("%d", &priorita);
    getchar();
    a->importanza = (Priorita)priorita;

    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;
}

// Modifica di un'attività
void modifica_attivita(Attivita *a) {
    printf("*** NUOVA DESCRZIONE ***: ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = 0;

    printf("*** NUOVO CORSO ***: ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = 0;

    printf("*** NUOVA DATA DI SCADENZA (GG/MM/AAAA) ***: ");
    fgets(a->data_di_scadenza, sizeof(a->data_di_scadenza), stdin);
    a->data_di_scadenza[strcspn(a->data_di_scadenza, "\n")] = 0;

    printf("*** NUOVO TEMPO STIMATO (ORE) ***: ");
    scanf("%d", &a->tempo_stimato);
    getchar();

    int priorita;
    printf("*** NUOVA PRIORITA' (BASSA = 1, MEDIA = 2, ALTA = 3) ***: ");
    scanf("%d", &priorita);
    getchar();
    a->importanza = (Priorita)priorita;
}

// Funzione per verificare ritardo
int verifica_ritardo(const char *data_di_scadenza) {
    time_t t = time(NULL);
    struct tm *tm_corrente = localtime(&t);
    int giorno, mese, anno;

    sscanf(data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);
    if (anno < tm_corrente->tm_year + 1900 ||
        (anno == tm_corrente->tm_year + 1900 && mese < tm_corrente->tm_mon + 1) ||
        (anno == tm_corrente->tm_year + 1900 && mese == tm_corrente->tm_mon + 1 && giorno < tm_corrente->tm_mday)) {
        return 1;
    }
    return 0;
}

// Mostra un'attività
void mostra_attivita(const Attivita *a) {
    printf("*** DESCRIZIONE ***: %s\n", a->descrizione);
    printf("*** CORSO ***: %s\n", a->corso);
    printf("*** SCADENZA ***: %s\n", a->data_di_scadenza);
    printf("*** TEMPO STIMATO ***: %d ORE \n", a->tempo_stimato);
    printf("*** PRIORITA' ***: %s\n", (a->importanza == ALTA) ? "ALTA" : (a->importanza == MEDIA) ? "MEDIA" : "BASSA");
    printf("*** STATO ***: %s\n", (a->stato == IN_RITARDO) ? "IN RITARDO" : (a->stato == COMPLETATA) ? "COMPLETATA" : "IN CORSO");
}
