#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "coda_priorita.h"

//Creazione di una nuova coda di priorità
PCoda nuova_PC(void) {
    PCoda c = malloc(sizeof(CodaPriorita));
    if (!c) return NULL;
    c->num_elementi = 0;
    return c;
}

// Verifica se la coda è vuota
int vuota_PC(PCoda c) {
    return !c || c->num_elementi == 0;
}

// Inserisce un'attività nella coda e riordina l'heap
int inserisci(PCoda c, Attivita nuovaAttivita) {
    if (!c || c->num_elementi >= MAX_HEAP) 
        return 0;

    c->num_elementi++;
    c->vet[c->num_elementi] = nuovaAttivita;

    // Riordina l'heap (heap max in base all'importanza)
    int pos = c->num_elementi, i = pos / 2;

    Attivita temp;

    while (pos > 1 && c->vet[pos].importanza > c->vet[i].importanza) {
          temp = c->vet[i];
          c->vet[i] = c->vet[pos];
          c->vet[pos] = temp;
          pos = i;
          i = pos / 2;
    }
    return 1;
}

// Restituisce l'attività con massima priorità
Attivita ottieni_max(PCoda c) {
    if (vuota_PC(c)) {
        Attivita vuota = { "Nessuna attivita'", "", "00/00/0000", 0, BASSA, COMPLETATA, 0 };
        return vuota;
    }
    return c->vet[1];
}

// Visualizza il progresso di tutte le attività
void mostra_progresso(PCoda c) {

    if (vuota_PC(c)) {
        printf("===========================================\n");
        printf("   NON RISULTA PRESENTE NESSUNA ATTIVITA'\n");
        printf("===========================================\n");
        return;
    }

    printf("===========================================\n");
    printf("         PROGRESSO DELLE ATTIVITA'\n");
    printf("===========================================\n\n");

    for (int i = 1; i <= c->num_elementi; i++) {
        printf("Attivita' %d\n", i);
        printf("Descrizione    : %s\n", c->vet[i].descrizione);
        printf("Corso          : %s\n", c->vet[i].corso);
        printf("Scadenza       : %s\n", c->vet[i].data_di_scadenza);
        printf("Tempo stimato  : %d ore\n", c->vet[i].tempo_stimato);

        printf("Priorita'      : %s\n",    (c->vet[i].importanza == ALTA) ? "ALTA" :   (c->vet[i].importanza == MEDIA) ? "MEDIA" : "BASSA");

        printf("Stato          : %s\n",  (c->vet[i].stato == IN_RITARDO) ? "In Ritardo" : (c->vet[i].stato == COMPLETATA) ? "Completata" : "In Corso");

        printf("Progresso      : %d%%\n", c->vet[i].progresso);
        
        printf("Data Completamento : %s\n" , c->vet[i].data_completamento);

        printf("-------------------------------------------\n");
    }
    printf("\n");
}

// Genera un report settimanale delle attività in base alla data di scadenza

void genera_report_settimanale(PCoda c) {

    time_t attuale = time(NULL);
    struct tm *corrente = localtime(&attuale);
    struct tm inizioSettimana = *corrente;

    //Calcola l'inizio della settimana (Lunedì è impostato come inizio della settimana)

    int diff = (corrente->tm_wday == 0 ? 6 : corrente->tm_wday - 1);
    inizioSettimana.tm_mday -= diff;
    inizioSettimana.tm_hour = 0;
    inizioSettimana.tm_min = 0;
    inizioSettimana.tm_sec = 0;
    time_t start_t = mktime(&inizioSettimana);

    //Fine della settimana impostata a Domenica alle ore 23:59:59
    struct tm fineSettimana = inizioSettimana;
    fineSettimana.tm_mday += 6;
    fineSettimana.tm_hour = 23;
    fineSettimana.tm_min = 59;
    fineSettimana.tm_sec = 59;
    time_t end_t = mktime(&fineSettimana);

    int contaCompletate = 0, contaInCorso = 0, contaInRitardo = 0;

    printf("===========================================\n");
    printf("  REPORT SETTIMANALE DELLE ATTIVITA'\n");
    printf("===========================================\n\n");

    for (int i = 1; i <= c->num_elementi; i++) {

        Attivita a = c->vet[i];

        int giorno, mese, anno;

        // Se l'attività è completata, usa la data di completamento,
        // altrimenti usa la data di scadenza.
        if(a.stato == COMPLETATA) {
            if(strlen(a.data_completamento) > 0)
                sscanf(a.data_completamento, "%d/%d/%d", &giorno, &mese, &anno);

            else
                sscanf(a.data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);

        }   else {
            sscanf(a.data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);
        }

        struct tm tmData = {0};
        tmData.tm_mday = giorno;
        tmData.tm_mon = mese - 1;
        tmData.tm_year = anno - 1900;
        tmData.tm_hour = 0;
        tmData.tm_min = 0;
        tmData.tm_sec = 0;
        time_t dataTask = mktime(&tmData);

        if(dataTask >= start_t && dataTask <= end_t) {

            if(a.stato == COMPLETATA) {

                printf("Attivita' COMPLETATA: %s (%s) Completata: %s, Progresso: %d%%\n",
                       a.descrizione, a.corso, (strlen(a.data_completamento) > 0 ? a.data_completamento : a.data_di_scadenza), a.progresso);
                       contaCompletate++;

            } else if(a.stato == IN_CORSO) {

                printf("Attivita' IN CORSO  : %s (%s) Scadenza: %s, Progresso: %d%%\n",  a.descrizione, a.corso, a.data_di_scadenza, a.progresso);
                       contaInCorso++;

            } else if(a.stato == IN_RITARDO) {

                printf("Attivita' IN RITARDO: %s (%s) Scadenza: %s, Progresso: %d%%\n", a.descrizione, a.corso, a.data_di_scadenza, a.progresso);
                       contaInRitardo++;
            }
        }
    }
    printf("\n===========================================\n");

    printf("Riepilogo Settimanale:\n\n");
    printf("Attivita' COMPLETATE: %d\n", contaCompletate);
    printf("Attivita' IN CORSO    : %d\n", contaInCorso);
    printf("Attivita' IN RITARDO  : %d\n", contaInRitardo);

    printf("===========================================\n\n");

    printf("PREMI INVIO PER CONTINUARE...");
    while(getchar() != '\n');
}

// Eliminazione di un'attività mantenendo l'heap ordinato
void elimina_attivita(PCoda c) {
    if (vuota_PC(c)) {
        printf("===========================================\n");
        printf("   NON RISULTA PRESENTE NESSUNA ATTIVITA'\n");
        printf("===========================================\n");
        return;
    }

    char descrizione[100];

    printf("===========================================\n");
    printf("INSERISCI LA DESCRIZIONE DELL'ATTIVITA' DA ELIMINARE:\n");
    printf("===========================================\n");

    fgets(descrizione, sizeof(descrizione), stdin);
    descrizione[strcspn(descrizione, "\n")] = '\0';

    int indice = -1;

    for (int i = 1; i <= c->num_elementi; i++) {

        if (strcmp(c->vet[i].descrizione, descrizione) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        c->vet[indice] = c->vet[c->num_elementi--];

        // Riordino l'heap dopo la rimozione
        int i = indice, figlio;

        Attivita temp;
        while (2 * i <= c->num_elementi) {
            figlio = 2 * i;

            if (figlio < c->num_elementi && c->vet[figlio].importanza < c->vet[figlio + 1].importanza)
                figlio++;

            if (c->vet[i].importanza >= c->vet[figlio].importanza)
                break;

            temp = c->vet[i];
            c->vet[i] = c->vet[figlio];
            c->vet[figlio] = temp;
            i = figlio;
        }

        printf("===========================================\n");
        printf("  HAI ELIMINATO L'ATTIVITA' CON SUCCESSO!\n");
        printf("===========================================\n");

    } else {

        printf("===========================================\n");
        printf("   ATTIVITA' NON TROVATA!\n");
        printf("===========================================\n");
    }
}
