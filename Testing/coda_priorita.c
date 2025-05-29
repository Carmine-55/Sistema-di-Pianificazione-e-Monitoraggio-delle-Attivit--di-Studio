#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "coda_priorita.h"

#define MAX_HEAP 50


struct CodaPriorita {

    Attivita vet[MAX_HEAP];  
    int num_elementi;

};



/* ----------------------------------------------------------------

- Funzione: nuova_PC

- Crea e inizializza una nuova coda di priorità

- Specifica sintattica:  PCoda nuova_PC(void) -> PCoda

- Parametri: (Nessuno parametro)

- Specifica semantica: nuova_PC() -> PCoda

- Pre-Condizioni: (Nessuna)

- Post-Condizioni: Restituisce un oggetto di tipo PCoda
                   Altrimenti NULL in caso di fallimento dell'allocazione

- Ritorna: Un oggetto di tipo PCoda 
           Altrimenti NULL
      
- Effetti collaterali: Viene allocata dinamicamente della memoria che deve essere liberata tramite free()         

*/


PCoda nuova_PC(void) {

    PCoda c = malloc(sizeof(struct CodaPriorita));

    if (!c)
    return NULL;

    c->num_elementi = 0;
    return c;
}


/* ----------------------------------------------------------------

- Funzione: vuota_PC

- Verifica se la coda di priorità è vuota oppure non è stata inizializzata

- Specifica sintattica: int vuota_PC(PCoda) -> int

- Parametri: 
             c: PCoda

- Specifica semantica:  vuota_PC(c) -> int

- Pre-Condizioni: Il parametro inserito deve essere di tipo PCoda (oppure NULL)

- Post-Condizioni: Restituisce 1 se la coda è vuota o non inizializzata
                   Altrimenti 0

- Ritorna: 1 se la coda è vuota o non valida
           0 se contiene almeno un elemento

- Effetti collaterali: (Nessuno)           

*/


int vuota_PC(PCoda c) {

    return !c || c->num_elementi == 0;
}


/* ----------------------------------------------------------------

- Funzione: inserisci

- Inserisce un nuovo elemento di tipo 'Attivita' in una coda organizzata con max-heap

- Specifica sintattica:  int inserisci(PCoda, Attivita) -> int

- Parametri: 
             c: PCoda
             nuovaAttivita: Attivita 
      
- Specifica semantica:  inserisci(c, nuovaAttivita) -> int   

- Pre-Condizioni: La coda deve essere inizializzata e avere spazio sufficiente, ovvero (numero elementi < MAX_HEAP)

- Post-Condizioni: La coda mantiene sempre la proprietà del max-heap e contiene l'elemento inserito

- Ritorna: 1 se l'elemento è stato inserito con successo
           0 altrimenti

- Effetti collaterali: La struttura di tipo PCoda viene modificata           

*/


int inserisci(PCoda c, Attivita nuovaAttivita) {

    if (!c || c->num_elementi >= MAX_HEAP)

    return 0;

    c->num_elementi++;
    c->vet[c->num_elementi] = nuovaAttivita;

    int pos = c->num_elementi, i = pos / 2;

    Attivita temp;

    //Continua finchè l'elemento corrente ha importanza maggiore del genitore

    while (pos > 1 && c->vet[pos].importanza > c->vet[i].importanza) {

         //Scambia il genitore con il figlio per mantenere il max-heap

        temp = c->vet[i];
        c->vet[i] = c->vet[pos];
        c->vet[pos] = temp;

        
        pos = i;        //Aggiorna la posizione corrente con quella del genitore


        i = pos / 2;    //Calcola il nuovo indice del genitore 
    }

    return 1;
}



/* ----------------------------------------------------------------

-Funzione: ottieni_max

- Restituisce l'elemento con il massimo valore di importanza dalla coda di priorità

- Specifica sintattica:   Attivita ottieni_max(PCoda) -> Attivita

- Parametri: 
             c: PCoda

- Specifica semantica:  ottieni_max(c) -> Attivita

- Pre-Condizioni: (Nessuna)

- Post-Condizioni: Se la coda è vuota viene restituita una 'Attivita' predefinita
                   Altrimenti, l'elemento in cima.

- Ritorna: l'oggetto di tipo 'Attivita' con il maggior grado di importanza

- Effetti collaterali: (Nessuno)

*/


Attivita ottieni_max(PCoda c) {

    Attivita vuota = { "Nessuna attivita'", "", "00/00/0000", 0, BASSA, COMPLETATA, 0, "" };

    if (vuota_PC(c))
    return vuota;

    return c->vet[1];
}



/* ----------------------------------------------------------------

- Funzione: mostra_progresso

- Permette di visualizzare i dettagli e i progressi degli elementi presenti nella coda

- Specifica sintattica: void mostra_progresso(PCoda) -> void

- Parametri: 
             c: PCoda

- Specifica semantica:  mostra_progresso(c) -> void

- Pre-Condizioni: La coda deve essere inizializzata

- Post-Condizioni: I dettagli degli elementi vengono stampati a schermo

- Ritorna: (Nessun valore)

- Effetti collaterali: Stampa l'output a schermo

*/


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
        printf("Priorita'      : %s\n", (c->vet[i].importanza == ALTA) ? "ALTA" : (c->vet[i].importanza == MEDIA) ? "MEDIA" : "BASSA");
        printf("Stato          : %s\n", (c->vet[i].stato == IN_RITARDO) ? "In Ritardo" : (c->vet[i].stato == COMPLETATA) ? "Completata" : "In Corso");
        printf("Progresso      : %d%%\n", c->vet[i].progresso);
        printf("Data Completamento : %s\n", c->vet[i].data_completamento);

        printf("-------------------------------------------\n");
    }

    printf("\n");
}

/* ----------------------------------------------------------------

- Funzione: genera_report_settimanale

- Genera un report dei dati temporali di tutti gli elementi della coda a priorità 
  che rientrano nella settimana corrente

- Specifica sintattica:  void genera_report_settimanale(PCoda) -> void

- Parametri: 
             c: PCoda

- Specifica semantica:  genera_report_settimanale(c) -> void   

- Pre-Condizioni: La coda deve essere inizializzata

- Post-Condizioni: Viene visualizzato un report di riepilogo degli elementi filtrati per intervallo

- Ritorna: (Nessun valore)

- Effetti collaterali: Stampa l'output a schermo

*/


void genera_report_settimanale(PCoda c) {

    time_t attuale = time(NULL);

    struct tm *corrente = localtime(&attuale);

    struct tm inizioSettimana = *corrente;          //Calcola l'inizio della settimana, ovvero (Lunedì alle 00:00:00)

    int diff = (corrente->tm_wday == 0 ? 6 : corrente->tm_wday - 1);

    inizioSettimana.tm_mday -= diff;
    inizioSettimana.tm_hour = 0;
    inizioSettimana.tm_min = 0;
    inizioSettimana.tm_sec = 0;

    time_t start_t = mktime(&inizioSettimana);

    struct tm fineSettimana = inizioSettimana;      //Calcola la fine della settimana, ovvero (Domenica alle 23:59:59)

    fineSettimana.tm_mday += 6;
    fineSettimana.tm_hour = 23;
    fineSettimana.tm_min = 59;
    fineSettimana.tm_sec = 59;

    time_t end_t = mktime(&fineSettimana);


    int contaCompletate = 0, contaInCorso = 0, contaInRitardo = 0;

    printf("===========================================\n");
    printf("  REPORT SETTIMANALE DELLE ATTIVITA'\n");
    printf("===========================================\n\n");

     //Esamina le attività per vedere se risultano nell'intervallo della settimana corrente 

    for (int i = 1; i <= c->num_elementi; i++) {

        Attivita a = c->vet[i];

        int giorno, mese, anno;


        //Usa la data di completamento solo se è disponibile, altrimenti utilizza la data di scadenza

        if(a.stato == COMPLETATA) {

            if(strlen(a.data_completamento) > 0)

                sscanf(a.data_completamento, "%d/%d/%d", &giorno, &mese, &anno);

            else
                sscanf(a.data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);

        }   else {
                sscanf(a.data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);
        }

        struct tm tmData = {0};          //Crea una struttura temporanea per la data della task
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

                printf("Attivita' IN CORSO  : %s (%s) Scadenza: %s, Progresso: %d%%\n",
                       a.descrizione, a.corso, a.data_di_scadenza, a.progresso);
                       contaInCorso++;

            } else if(a.stato == IN_RITARDO) {

                printf("Attivita' IN RITARDO: %s (%s) Scadenza: %s, Progresso: %d%%\n",
                       a.descrizione, a.corso, a.data_di_scadenza, a.progresso);
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



/* ----------------------------------------------------------------

- Funzione: elimina_attivita

- Rimuove un elemento di tipo 'Attivita' basandosi sulla descrizione inserita e
  aggiorna l'ordinamento per mantenere il max-heap

- Specifica sintattica: void elimina_attivita(PCoda) -> void

- Parametri:
            c: PCoda

- Specifica semantica:  elimina_attivita(c) -> void 

- Pre-Condizioni: La coda deve essere inizializzata e contenere almeno un elemento

- Post-Condizioni: L'elemento corrispondente alla ricerca viene eliminato e la 
                   struttura mantiene il max-heap

- Ritorna: (Nessun valore)           

- Effetti collaterali: Modifica la struttura di tipo PCoda

*/

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
    

    //Cerca l'attività corrispondente alla descrizione fornita

    int indice = -1;

    for (int i = 1; i <= c->num_elementi; i++) {

        if (strcmp(c->vet[i].descrizione, descrizione) == 0) {

            indice = i;

            break;
        }
    }
    
     //Sostituisce l'elemento da eliminare con l'ultimo elemento e diminuisce la dimensione della coda

    if (indice != -1) {

        c->vet[indice] = c->vet[c->num_elementi--];

        int i = indice, figlio;

        Attivita temp;

        while (2 * i <= c->num_elementi) {

            figlio = 2 * i;

            if (figlio < c->num_elementi && c->vet[figlio].importanza < c->vet[figlio + 1].importanza)
                figlio++;


            //Se l'elemento corrente è maggiore o uguale al figlio, allora l'heap risulta ordinato

            if (c->vet[i].importanza >= c->vet[figlio].importanza)
                break;

            //Scambia l'elemento corrente con il figlio più grande     

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



/* ----------------------------------------------------------------

- Funzione: mostra_notifiche

- Permette di visualizzare in output le notifiche relative agli elementi in ritardo

- Specifica sintattica:  void mostra_notifiche(PCoda) -> void

- Parametri:
             c: PCoda

- Specifica semantica:   mostra_notifiche(c) -> void

- Pre-Condizioni: Il parametro deve essere di tipo PCoda e rappresentare una collezione valida

- Post-Condizioni: Le notifiche, se presenti, vengono mostrate su schermo altrimenti viene 
                   visualizzato un messaggio indicante l'assenza di elementi in ritardo

- Ritorna: (Nessun valore)       

- Effetti collaterali:  Stampa l'output a schermo


*/


void mostra_notifiche(PCoda c) {  

    int notificaPresente = 0;

    printf("===========================================\n");
    printf("      PROMEMORIA: ATTIVITA' IN RITARDO\n");
    printf("===========================================\n\n");


    for (int i = 1; i <= c->num_elementi; i++) {

        if (c->vet[i].stato == IN_RITARDO) {

            printf("Attivita': %s\n", c->vet[i].descrizione);
            printf("Scadenza : %s\n", c->vet[i].data_di_scadenza);
            printf("Progresso: %d%%\n", c->vet[i].progresso);
            printf("-------------------------------------------\n");

            notificaPresente = 1;
        }
    }

    if (!notificaPresente)

        printf("NESSUNA ATTIVITA' E' IN RITARDO!\n");

        printf("\nPREMI INVIO PER CONTINUARE");

        while(getchar() != '\n');         //Pulisco il buffer di input ed elimino i caratteri residui fino a '\n'
}



/* ----------------------------------------------------------------

- Funzione: ottieni_numero_attivita

- Restituisce il numero di attività presenti nella coda

- Specifica sintattica:  int ottieni_numero_attivita(PCoda) -> int

- Parametri: 
             c: PCoda

- Specifica semantica:  ottieni_numero_attivita(c) -> int

- Pre-Condizioni:  La coda deve essere inizializzata (anche se vuota)

- Post-Condizioni:  Viene restituito il numero di attività contenute nella coda
                    Altrimenti, se la coda è NULL 0

- Ritorna:  Un intero che rappresenta il numero di elementi nella coda

- Effetti collaterali: (Nessuno)


*/


int ottieni_numero_attivita(PCoda c) {

    return (c) ? c->num_elementi : 0;
}


/* ----------------------------------------------------------------

- Funzione: ottieni_attivita

- Restituisce una copia dell'attività presente nella coda in corrispondenza dell'indice
  che è stato fornito


- Specifica sintattica:  Attivita ottieni_attivita(PCoda, int) -> Attivita

- Parametri:
             c: PCoda
             indice: int

- Specifica semantica:  ottieni_attivita(c, indice) -> Attivita

- Pre-Condizioni: La coda deve essere inizializzata e l'indice deve essere compreso tra 1 e il numero di elementi

- Post-Condizioni: Viene restituita una copia corretta dell'attività se l'indice è valido,
                   oppure un'attività vuota se l'indice non è valido

- Ritorna:  Un oggetto di tipo Attivita contenente i dati dell'attività richiesta oppure un oggetto "vuoto"

- Effetti collaterali: (Nessuno)

*/

Attivita ottieni_attivita(PCoda c, int indice) {

    Attivita vuota = { "","", "", 0, BASSA, COMPLETATA, 0, "" };

    if (!c || indice < 1 || indice > c->num_elementi)

    return vuota;

    return c->vet[indice];
}



/* ----------------------------------------------------------------

- Funzione: ottieni_attivita_puntatore

- Restituisce il puntatore all'attività presente nella coda in corrispondenza dell'indice fornito,
  consentendo di modificarla direttamente

- Specifica sintattica: 

- Parametri:  c: PCoda
              indice: int

- Specifica semantica:  ottieni_attivita_puntatore(c, indice) -> Attivita*

- Pre-Condizioni: La coda deve essere inizializzata e l'indice deve essere compreso tra 1 e il numero totale di elementi

- Post-Condizioni:  Viene restituito un puntatore valido all'attività se l'indice è corretto
                     Altrimenti NULL se l'indice non è valido

- Ritorna: Un puntatore all'elemento di tipo 'Attivita' richiesto oppure NULL in caso di indice non valido

- Effetti collaterali:  (Nessuno)

*/


Attivita* ottieni_attivita_puntatore(PCoda c, int indice) {

    if (!c || indice < 1 || indice > c->num_elementi)

    return NULL;

    return &c->vet[indice];
}    
