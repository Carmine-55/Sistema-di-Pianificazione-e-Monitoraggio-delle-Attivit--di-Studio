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
        printf("****** NON RISULTA PRESENTE NESSUNA ATTIVITA' ******\n");
        return;
    }

    char descrizione[100];
    printf("****** INSERISCI LA DESCRIZIONE DELL'ATTIVITA' CHE DESIDERI ELIMINARE ******: ");
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
        // Sostituisci l'elemento eliminato con l'ultimo e riduci il numero di elementi
        c->vet[indice] = c->vet[c->num_elementi--]; 

        //Procedura che serve a ripristinare l'heap dopo una rimozione 
        int i = indice, figlio;
        Attivita temp;

        while (2 * i <= c->num_elementi) {
            figlio = 2 * i;                   //Calcolo l'indice del figlio sinistro
            
            //Se esiste un figlio destro più importante del sinistro, allora scelgo lui
            if (figlio < c->num_elementi && c->vet[figlio].importanza < c->vet[figlio + 1].importanza)
                figlio++;
            
            //Se il nodo corrente ha un'importanza maggiore o uguale al figlio, allora l'heap è già corretto
            if (c->vet[i].importanza >= c->vet[figlio].importanza)
                break;
            
            // Scambio l'elemento corrente con il figlio più importante per mantenere la proprietà dell'heap
            temp = c->vet[i];
            c->vet[i] = c->vet[figlio];
            c->vet[figlio] = temp;

            i = figlio;  //Aggiorna l'indice per continuare la discesa nel sottoalbero
        }

        printf("****** HAI ELIMINATO L'ATTIVITA' CON SUCCESSO! ******\n");
    } else {
        printf("****** L'ATTIVITA' NON E' STATA TROVATA ******\n");
    }
}


void mostra_progresso(PCoda c) {
    if (vuota_PC(c)) {
        printf("******NON RISULTA PRESENTE NESSUNA ATTIVITA'.******\n");
        return;
    }

    printf("\n****** PROGRESSO DELLE ATTIVITA' ****** \n");
    for (int i = 1; i <= c->num_elementi; i++) {
        printf("%d. %s (%s) - Scadenza: %s - Tempo stimato: %d ore - Priorita'(BASSA = 1, MEDIA = 2, ALTA = 3): %d - Stato: %s\n",
               i, c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza,
               c->vet[i].tempo_stimato, c->vet[i].importanza,
               (c->vet[i].stato == IN_RITARDO) ? "In Ritardo" : 
               (c->vet[i].stato == COMPLETATA) ? "Completata" : "In Corso");
    }
}

void genera_report_settimanale(PCoda c) {
    if (vuota_PC(c)) {
        printf("******NON RISULTA PRESENTE NESSUNA ATTIVITA'.******\n");
        return;
    }

    printf("\n****** REPORT SETTIMANALE DELLE ATTIVITA' ******\n");
    printf("\n *** ATTIVITA' COMPLETATE ***:\n");
    for (int i = 1; i <= c->num_elementi; i++) {
        if (c->vet[i].stato == COMPLETATA) {
            printf("%s (%s)\n", c->vet[i].descrizione, c->vet[i].corso);
        }
    }
    printf("\n *** ATTIVITA' IN CORSO ***:\n");
    for (int i = 1; i <= c->num_elementi; i++) {
        if (c->vet[i].stato == IN_CORSO) {
            printf("%s (%s) - Scadenza: %s\n", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza);
        }
    }
    printf("\n *** ATTIVITA' IN RITARDO ***:\n");
    for (int i = 1; i <= c->num_elementi; i++) {
        if (c->vet[i].stato == IN_RITARDO) {
            printf("%s (%s) - Scadenza: %s\n", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza);
        }
    }
}

void completa_un_attivita(PCoda c) {
    if (vuota_PC(c)) {
        printf("\n***NON CI SONO ATTIVITA' DA COMPLETARE! ***\n");
        return;
    }

    char descrizione[100];
    printf("*** INSERISCI LA DESCRIZIONE DELL'ATTIVITA' COMPLETATA ***: ");
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
        printf("ATTIVITA' COMPLETATA: %s\n", c->vet[indice].descrizione);
    } else {
        printf(" ATTIVITA' NON TROVATA!\n");
    }
}
