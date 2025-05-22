#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "item.h"

// Aggiunta di un'attività
int aggiungi_attivita(Attivita *a) {

    printf("===========================================\n");
    printf("        INSERIMENTO ATTIVITA''\n");
    printf("===========================================\n\n");

     printf("Inserisci la Descrizione    : ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = 0;

    if(strlen(a->descrizione) == 0){
        printf("ERRORE! NON HAI INSERITO NESSUNA DESCRIZIONE...\n");
        return 0;
    }

    printf("Inserisci il Nome del Corso : ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = 0;

    if(strlen(a->corso) == 0){
        printf("ERRORE! NON HAI INSERITO IL NOME DEL CORSO...");
        return 0;
    }

    int giorno, mese, anno;
    printf("Inserisci la Data di Scadenza (GG/MM/AAAA): ");
          if (scanf("%d/%d/%d", &giorno, &mese, &anno) != 3) {
          printf("\nERRORE IL FORMATO DELLA DATA NON E' VALIDO...RIPROVA\n");
          while(getchar() != '\n');  // Pulisce il buffer
          return 0;
    }
    getchar();

    if (giorno < 1 || giorno > 31 || mese < 1 || mese > 12 || anno < 1900) {
        printf("\nERRORE! LA DATA INSERITA NON E' VALIDA\n");
        return 0;
    }
    sprintf(a->data_di_scadenza, "%02d/%02d/%04d", giorno, mese, anno);

    printf("Inserisci il Tempo Stimato (ore): ");
         if (scanf("%d", &a->tempo_stimato) != 1) {
         printf("\nERRORE! VALORE INSERITO NON VALIDO...RIPROVA\n");
         while(getchar() != '\n');
         return 0;
    }
    getchar();

    if(a->tempo_stimato < 1 || a->tempo_stimato > 10000){
        printf("ERRORE! IL VALORE INSERITO NON RIENTRA TRA QUELLI AMMESSI...");
        return 0;
    }

    int priorita;
    printf("Inserisci la Priorita' (BASSA = 1, MEDIA = 2, ALTA = 3): ");
          if (scanf("%d", &priorita) != 1) {
          printf("\nERRORE! PRIORITA' INSERITA NON VALIDA...RIPROVA\n");
          while(getchar() != '\n');
          return 0;
    }
    getchar();

    if(priorita < 1 || priorita > 3){
        printf("ERRORE! DEVI INSERIRE UN VALORE DA 1 A 3...");
        return 0;
    }

    a->importanza = (Priorita)priorita;

    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;

    printf("\n HAI AGGIUNTO L'ATTIVITA' CON SUCCESSO!\n");
    printf("===========================================\n\n");

    return 1; //Ritorna 1 se l'attività inserita è valida
}

// Modifica di un'attività
void modifica_attivita(Attivita *a) {
    
    printf("===========================================\n");
    printf("    MODIFICA DELL'ATTIVITA' SELEZIONATA\n");
    printf("===========================================\n\n");

    printf("Nuova Descrizione    : ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = 0;

    printf("Nuovo Nome del Corso : ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = 0;

    printf("Nuova Data di Scadenza (GG/MM/AAAA): ");
    fgets(a->data_di_scadenza, sizeof(a->data_di_scadenza), stdin);
    a->data_di_scadenza[strcspn(a->data_di_scadenza, "\n")] = 0;

    printf("Nuovo Tempo Stimato (ore): ");
          if (scanf("%d", &a->tempo_stimato) != 1) {
          printf("\nERRORE! IL VALORE INSERITO NON RIENTRA TRA QUELLI AMMESSI...\n");
          while(getchar() != '\n');
          return;
    }
    getchar();

    int priorita;
    printf("Nuova Priorita' (BASSA = 1, MEDIA = 2, ALTA = 3): ");
          if (scanf("%d", &priorita) != 1) {
          printf("\nERRORE! PRIORITA' INSERITA NON VALIDA...RIPROVA\n");
          while(getchar() != '\n');
          return;
    }

    getchar();

    a->importanza = (Priorita)priorita;

    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;

    printf("\nHAI MODIFICATO L'ATTIVITA' CON SUCCESSO!\n");
    printf("===========================================\n\n");
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
    printf("===========================================\n");
    printf("              DETTAGLI ATTIVITA'\n");
    printf("===========================================\n");

    printf("Descrizione    : %s\n", a->descrizione);
    printf("Corso          : %s\n", a->corso);
    printf("Scadenza       : %s\n", a->data_di_scadenza);
    printf("Tempo stimato  : %d ore\n", a->tempo_stimato);
    printf("Priorita'       : %s\n", 
           (a->importanza == ALTA) ? "ALTA" : 
           (a->importanza == MEDIA) ? "MEDIA" : "BASSA");

    printf("Stato          : %s\n", 
           (a->stato == IN_RITARDO) ? "IN RITARDO" :
           (a->stato == COMPLETATA) ? "COMPLETATA" : "IN CORSO");

    printf("===========================================\n\n");
}