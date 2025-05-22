#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coda_priorita.h"
#include "item.h"

// Creazione di una nuova coda di priorità
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

// Inserisce un'attività nella coda e riordina il heap
int inserisci(PCoda c, Attivita nuovaAttivita) {
    if (!c || c->num_elementi >= MAX_HEAP) 
    return 0;

    c->num_elementi++;
    c->vet[c->num_elementi] = nuovaAttivita;

    // Riordina l'heap
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

// Ottieni l'attività con massima priorità
Attivita ottieni_max(PCoda c) {
    if (vuota_PC(c)) {
        Attivita vuota = { "Nessuna attivita'", "", "00/00/0000", 0, BASSA, COMPLETATA };
        return vuota;
    }
    return c->vet[1];
}

// Eliminazione di un'attività scelta dall'utente mantenendo il heap ordinato
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
        // Sostituzione con l'ultimo elemento e riduzione del numero degli elementi
        c->vet[indice] = c->vet[c->num_elementi--]; 

        // Riordino dell'heap dopo la rimozione
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
        printf("Priorita'      : %s\n", 
               (c->vet[i].importanza == ALTA) ? "ALTA" : 
               (c->vet[i].importanza == MEDIA) ? "MEDIA" : "BASSA");
        printf("Stato          : %s\n", 
               (c->vet[i].stato == IN_RITARDO) ? "In Ritardo" : 
               (c->vet[i].stato == COMPLETATA) ? "Completata" : "In Corso");
        printf("-------------------------------------------\n");
    }
    printf("\n");
}

void genera_report_settimanale(PCoda c) {
    if (vuota_PC(c)) {
        printf("===========================================\n");
        printf("   NON RISULTA PRESENTE NESSUNA ATTIVITA'\n");
        printf("===========================================\n");
        return;
    }

    printf("===========================================\n");
    printf("  REPORT SETTIMANALE DELLE ATTIVITA'\n");
    printf("===========================================\n\n");

    printf(">>> ATTIVITA' COMPLETATE:\n");
    for (int i = 1; i <= c->num_elementi; i++) {
        if (c->vet[i].stato == COMPLETATA) {
            printf("%s (%s)\n", c->vet[i].descrizione, c->vet[i].corso);
        }
    }
    printf("\n");

    printf(">>> ATTIVITA' IN CORSO:\n");
    for (int i = 1; i <= c->num_elementi; i++) {
        if (c->vet[i].stato == IN_CORSO) {
            printf("%s (%s) - Scadenza: %s\n", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza);
        }
    }
    printf("\n");

    printf(">>> ATTIVITA' IN RITARDO:\n");
    for (int i = 1; i <= c->num_elementi; i++) {
        if (c->vet[i].stato == IN_RITARDO) {
            printf("%s (%s) - Scadenza: %s\n", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza);
        }
    }
     printf("===========================================\n\n");
}

void completa_un_attivita(PCoda c) {
    if (vuota_PC(c)) {
        printf("===========================================\n");
        printf("   NON CI SONO ATTIVITA' DA COMPLETARE!\n");
        printf("===========================================\n\n");
        return;
    }

    char descrizione[100];

    printf("========================================================\n");
    printf("INSERISCI LA DESCRIZIONE DELL'ATTIVITA' COMPLETATA:\n");
    printf("========================================================\n");

    fgets(descrizione, sizeof(descrizione), stdin);
    descrizione[strcspn(descrizione, "\n")] = 0;

    int indice = -1;
    for (int i = 1; i <= c->num_elementi; i++) {
        if (strcmp(c->vet[i].descrizione, descrizione) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        c->vet[indice].stato = COMPLETATA;
        printf("===========================================\n");
        printf("  HAI COMPLETATO L'ATTIVITA' CON SUCCESSO!\n");
        printf("===========================================\n");

        printf("Descrizione    : %s\n", c->vet[indice].descrizione);
        printf("Corso          : %s\n", c->vet[indice].corso);
        printf("Scadenza       : %s\n", c->vet[indice].data_di_scadenza);
        printf("Tempo stimato  : %d ore\n", c->vet[indice].tempo_stimato);
        printf("-------------------------------------------\n\n");

    } else {

        printf("===========================================\n");
        printf("   ATTIVITA' NON TROVATA!\n");
        printf("===========================================\n\n");
    }
}
 
