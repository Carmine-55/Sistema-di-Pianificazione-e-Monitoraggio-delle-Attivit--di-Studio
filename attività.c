#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Coda_Priorità.h"
#include "Coda_Priorità.c"
#define MAX_ATTIVITA 50

//Definizione dell'enumerazione per la priorità delle attività
typedef enum{
    BASSA = 1,
    MEDIA = 2,
     ALTA = 3,
}Priorità;

//Definizione dell'enumerazione per lo stato dell'attività
typedef enum{
    IN_RITARDO,
    IN_CORSO,
    COMPLETATA,
}Stato;

typedef struct{
    char descrizione[150];               //Descrizione dell'attività                
    char corso[50];                      //Nome del corso a cui si fa riferimento
    char data_di_scadenza[11];           //Il formato deve essere gg/mm/aaaa
    int tempo_stimato;                   //In ore
    Priorità importanza;
    Stato stato;                   
}Attività;

void aggiungi_attività(PCoda c){

    if(c->num_elementi >= MAX_HEAP){
        printf("Hai raggiunto il numero massimo di attività! \n");
        return;
    }
    Attività nuovaAttività;

    printf("Inserisci la descrizione dell'attività: ");
    scanf(" %s", nuovaAttività.descrizione);

    printf("Inserisci nome del corso: ");
    scanf(" %s", nuovaAttività.corso);

    printf("Inserisci la data di scadenza dell'attività (gg/mm/aaaa): ");
    scanf(" %s", nuovaAttività.data_di_scadenza);

    printf("Inserisci il tempo stimato di completamento in ore: ");
    scanf(" %d", nuovaAttività.tempo_stimato);

    int prio;
    printf("Inserisci il grado di priorità (1 = BASSA, 2 = MEDIA, 3 = ALTA): ");
    scanf("%d", &prio);
    nuovaAttività.importanza = (Priorità) prio;

    nuovaAttività.stato = verifica_ritardo(nuovaAttività.data_di_scadenza) ? IN_RITARDO : IN_CORSO;

    inserisci(c, nuovaAttività);
    printf("Hai aggiunto una nuova attività con successo!");
}

void modifica_attività(PCoda c){

    if(vuota_PC(c)){
        printf("Non è disponibile nessuna attività.\n");
        return;
    }
    char descrizione[150];
     printf("Inserisci la descrizione dell'attività che vuoi modificare: ");
     scanf(" %s", descrizione);

     for(int i = 1; i <= c->num_elementi; i++){
        if(strcmp(c->vet[i].descrizione, descrizione) == 0){
            printf("Nuova descrizione: ");
            scanf(" %s", c->vet[i].descrizione);

            printf("Nuovo corso: ");
            scanf(" %s", c->vet[i].corso);

            printf("Nuova priorità (BASSA = 1, MEDIA = 2, ALTA = 3): ");

            int nuovaPriorità;
            scanf("%d", &nuovaPriorità);
            c->vet[i].importanza = (Priorità) nuovaPriorità;
            printf("Hai modificato l'attività con successo!\n");
            return;
        }
     }
      printf("Nessuna attività è stata trovata \n");
}

void elimina_attività(PCoda c){

    if(vuota_PC(c)){
        printf("Non è disponibile nessuna attività.\n");
        return;
    }
     char descrizione[150];
     printf("Inserisci la descrizione dell'attività che vuoi eliminare: ");
     scanf(" %s", descrizione);

      for(int i = 1; i <= c->num_elementi; i++){
        if(strcmp(c->vet[i].descrizione, descrizione) == 0){
            cancella_max(c);
            printf("Attività eliminata con successo!\n");
            return;
        }
      }
      printf("Nessuna attività è stata trovata \n");
} 

void visualizza_progresso(PCoda c){

    if(vuota_PC(c)){
        printf("Non è disponibile nessuna attività.\n");
        return;
    }
     printf("\n********PROGRESSO ATTIVITA'********\n");

     for(int i = 1; i <= c->num_elementi; i++){
        printf("Attivita: %s (%s) - Scadenza: %s - Priorità: %d - Stato: ", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza, c->vet[i].importanza);

        switch(c->vet[i].stato){
            case IN_RITARDO: printf("In Ritardo!\n");
            break;
            case IN_CORSO: printf("In Corso!\n");
            break;
            case COMPLETATA: printf("Completata!\n");
            break;
        }
     }
}

void genera_report_settimanale(PCoda c){

    if(vuota_PC(c)){
        printf("Non è disponibile nessuna attività.\n");
        return;
    }
    printf("\n********REPORT SETTIMANALE********\n");

    printf("\n Attività completate:\n");
    for(int i = 1; i <= c->num_elementi; i++){
        if(c->vet[i].stato == COMPLETATA){
            printf("%s (%s)\n", c->vet[i].descrizione, c->vet[i].corso);
        }
    }
    printf("\n Attività in corso:\n");
    for(int i = 1; i <= c->num_elementi; i++){
        if(c->vet[i].stato == IN_CORSO){
            printf("%s (%s)\n  - Scadenza: %s\n", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza);
        }
    }
    printf("\n Attività in ritardo:\n");
    for(int i = 1; i <= c->num_elementi; i++){
        if(c->vet[i].stato == IN_RITARDO){
            printf("%s (%s)\n  - Scadenza: %s\n", c->vet[i].descrizione, c->vet[i].corso, c->vet[i].data_di_scadenza);
        }
    }
}

int verifica_ritardo(const char* data_di_scadenza){
    time_t t = time(NULL);
    struct tm *tm_corrente = localtime(&t);
    int giorno, mese, anno;

    sscanf(data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);

    //Se l'anno della scadenza dell'attività è inferiore all'anno attuale, allora l'attività è in ritardo
    if(anno < tm_corrente->tm_year + 2000 

    //Se l'anno della scadenza dell'attività è uguale all'anno attuale, ma il mese è inferiore rispetto a quello attuale, allora l'attività è in ritardo
        || (anno == tm_corrente->tm_year + 2000 && mese < tm_corrente->tm_mon +1) 
     
    //Se l'anno e il mese della scadenza dell'attività sono uguali a quelli attuali, ma il giorno è inferiore all'attuale, allora l'attività è in ritardo    
        || (anno == tm_corrente->tm_year + 2000 && mese < tm_corrente-> tm_mon + 1 && giorno < tm_corrente->tm_mday)){
        return 1;         //Se l'attività è in ritardo ritorna 1
    } return 0;           //Se l'attività non è in ritardo  ritorna 0
}