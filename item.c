#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "item.h"

// Funzione per aggiungere una nuova attività, ioltre imposta il progresso a 0
int aggiungi_attivita(Attivita *a) {

    printf("===========================================\n");
    printf("        INSERIMENTO ATTIVITA'\n");
    printf("===========================================\n\n");

    //Inserimento della descrizione
    printf("Inserisci la Descrizione    : ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = '\0';

    if (strlen(a->descrizione) == 0) {
        printf("\nERRORE! NON HAI INSERITO NESSUNA DESCRIZIONE...\n");
        return 0;
    }

    // Inserimento nome corso
    printf("Inserisci il Nome del Corso : ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = '\0';

    if (strlen(a->corso) == 0) {
        printf("\nERRORE! NON HAI INSERITO IL NOME DEL CORSO...\n");
        return 0;
    }

    // Inserimento data di scadenza
    int giorno, mese, anno;

    printf("Inserisci la Data di Scadenza (GG/MM/AAAA): ");

    if (scanf("%d/%d/%d", &giorno, &mese, &anno) != 3) {
        printf("\nERRORE IL FORMATO DELLA DATA NON E' VALIDO...RIPROVA\n");
        while(getchar() != '\n');  // Pulisce il buffer
        return 0;
    }
    getchar();  // Pulisce il carattere '\n'

    if (giorno < 1 || giorno > 31 || mese < 1 || mese > 12 || anno < 1900) {
        printf("\nERRORE! LA DATA INSERITA NON E' VALIDA...\n");
        return 0;
    }
    sprintf(a->data_di_scadenza, "%02d/%02d/%04d", giorno, mese, anno);

    //Inserimento del tempo stimato
    printf("Inserisci il Tempo Stimato (ore): ");
    if (scanf("%d", &a->tempo_stimato) != 1) {
        printf("\nERRORE! VALORE INSERITO NON VALIDO...RIPROVA\n");
        while(getchar() != '\n');
        return 0;
    }
    getchar();

    if(a->tempo_stimato < 1 || a->tempo_stimato > 10000) {
        printf("\nERRORE! IL VALORE INSERITO NON RIENTRA TRA QUELLI AMMESSI...\n");
        return 0;
    }

    //Inserimento della priorità
    int priorita;

    printf("Inserisci la Priorita' (BASSA = 1, MEDIA = 2, ALTA = 3): ");

    if (scanf("%d", &priorita) != 1) {
        printf("\nERRORE! PRIORITA' INSERITA NON VALIDA...RIPROVA\n");
        while(getchar() != '\n');
        return 0;
    }
    getchar();

    if(priorita < 1 || priorita > 3) {
        printf("\nERRORE! DEVI INSERIRE UN VALORE DA 1 A 3...\n");
        return 0;
    }
    a->importanza = (Priorita)priorita;

    //Imposta il progresso iniziale a 0
    a->progresso = 0;
    
    //Pulisce la data di completamento
    a->data_completamento[0] = '\0';

    //Verifica dello stato in base alla data di scadenza
    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;

    printf("\nHAI AGGIUNTO L'ATTIVITA' CON SUCCESSO!\n");
    printf("===========================================\n\n");

    return 1;
}

// Modifica di un'attività esistente
void modifica_attivita(Attivita *a) {

    printf("===========================================\n");
    printf("    MODIFICA DELL'ATTIVITA' SELEZIONATA\n");
    printf("===========================================\n\n");

    //Aggiornamento della descrizione
    printf("Nuova Descrizione    : ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = '\0';

    //Aggiornamento nome del corso
    printf("Nuovo Nome del Corso : ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = '\0';

    //Aggiornamento della data di scadenza
    printf("Nuova Data di Scadenza (GG/MM/AAAA): ");
    fgets(a->data_di_scadenza, sizeof(a->data_di_scadenza), stdin);
    a->data_di_scadenza[strcspn(a->data_di_scadenza, "\n")] = '\0';

    //Aggiornamento del tempo stimato
    printf("Nuovo Tempo Stimato (ore): ");

     if (scanf("%d", &a->tempo_stimato) != 1) {
        printf("\nERRORE! VALORE INSERITO NON VALIDO...RIPROVA\n");
        while(getchar() != '\n');
        return;
    }
    getchar();

    //Aggiornamento della priorità
    int priorita;

    printf("Nuova Priorita' (BASSA = 1, MEDIA = 2, ALTA = 3): ");
    
     if (scanf("%d", &priorita) != 1) {
        printf("\nERRORE! PRIORITA' INSERITA NON VALIDA...RIPROVA\n");
        while(getchar() != '\n');
        return;
    }
    getchar();

    a->importanza = (Priorita)priorita;

    //Aggiornamento dello stato (rivalutazione in base alla data)
    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;

    printf("\nHAI MODIFICATO L'ATTIVITA' CON SUCCESSO!\n");
    printf("===========================================\n\n");
}

//Funzione per verificare se la data di scadenza è già passata, quindi verifica il ritardo
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

//Visualizza i dettagli dell' attività con priorità più alta
void mostra_attivita(const Attivita *a) {

    printf("===========================================\n");
    printf("              DETTAGLI ATTIVITA'\n");
    printf("===========================================\n");
    printf("Descrizione    : %s\n", a->descrizione);
    printf("Corso          : %s\n", a->corso);
    printf("Scadenza       : %s\n", a->data_di_scadenza);
    printf("Tempo stimato  : %d ore\n", a->tempo_stimato);

    printf("Priorita'      : %s\n", 
           (a->importanza == ALTA) ? "ALTA" : 
           (a->importanza == MEDIA) ? "MEDIA" : "BASSA");

    printf("Stato          : %s\n", 
           (a->stato == IN_RITARDO) ? "IN RITARDO" :
           (a->stato == COMPLETATA) ? "COMPLETATA" : "IN CORSO");

    printf("Progresso      : %d%%\n", a->progresso);

    printf("Data Completamento: %s\n" , a->data_completamento );

    printf("===========================================\n\n");
}

//Funzione che permette di aggiornare il progresso di un'attività, se il nuovo valore è 100 lo stato viene cambiato in COMPLETATA

void aggiorna_progresso_attivita(Attivita *a) {

    int nuovoProgresso;

    printf("INSERISCI LA NUOVA PERCENTUALE DI PROGRESSO PER '%s' (0-100): ", a->descrizione);

    if (scanf("%d", &nuovoProgresso) != 1) {
        printf("L'INPUT NON INSERITO NON E' VALIDO...\n");
        while (getchar() != '\n'); 
        return;
    }
    while (getchar() != '\n'); 

    if (nuovoProgresso < 0 || nuovoProgresso > 100) {
        printf("IL VALORE DI PROGRESSO INSERITO NON E' VALIDO! DEVE ESSERE COMPRESO TRA 0 E 100...\n");
        return;
    }

    a->progresso = nuovoProgresso;

    if (nuovoProgresso == 100) {
        a->stato = COMPLETATA;

        //Imposta la data di completamento al giorno corrente

        time_t adesso = time(NULL);
        struct tm *tempoCorrente = localtime(&adesso);
        sprintf(a->data_completamento, "%02d/%02d/%04d",
                tempoCorrente->tm_mday,
                tempoCorrente->tm_mon + 1,
                tempoCorrente->tm_year + 1900);

        printf("COMPLIMENTI! HAI COMPLETATO L'ATTIVITA' CON SUCCESSO...\n");

    } else {
        a->stato = IN_CORSO;
    }
    printf("PROGRESSO AGGIORNATO AL %d%% PER L'ATTIVITA' '%s'.\n", a->progresso, a->descrizione);
}
