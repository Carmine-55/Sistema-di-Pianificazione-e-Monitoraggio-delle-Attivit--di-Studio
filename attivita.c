#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "attivita.h"


/* ----------------------------------------------------------------

- Funzione: aggiungi_attivita

- Raccoglie in input i dati necessari per creare un nuovo elemento di tipo 'Attivita',
  inizializzando il progresso a 0 e determinando lo stato tramite un confronto temporale

- Specifica sintattica: int aggiungi_attivita(Attivita*) -> int

- Parametri: 
            a: Attivita*

- Specifica semantica:  aggiungi_attivita(a) -> int    

- Pre-Condizioni: Il puntatore deve riferirsi a una struttura di tipo 'Attivita' valida

- Post-Condizioni:  L'elemento di tipo 'Attivita' viene popolato e il suo progresso viene inizializzato a 0

- Ritorna: 1 se l'inserimento ha avuto successo
           0 altrimenti

- Effetti collaterali: Modifica il contenuto dell'oggetto 'Attivita'           

*/

int aggiungi_attivita(Attivita *a) {

    printf("===========================================\n");
    printf("        INSERIMENTO ATTIVITA'\n");
    printf("===========================================\n\n");


    printf("Inserisci la Descrizione    : ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = '\0';

    if (strlen(a->descrizione) == 0) {
        printf("\nERRORE! NON HAI INSERITO NESSUNA DESCRIZIONE...\n");
        return 0;
    }


    printf("Inserisci il Nome del Corso : ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = '\0';

    if (strlen(a->corso) == 0) {
        printf("\nERRORE! NON HAI INSERITO IL NOME DEL CORSO...\n");
        return 0;
    }

    int giorno, mese, anno;

    printf("Inserisci la Data di Scadenza (GG/MM/AAAA): ");

    if (scanf("%d/%d/%d", &giorno, &mese, &anno) != 3) {         //Controlla se il formato della data inserita è corretto 

        printf("\nERRORE IL FORMATO DELLA DATA NON E' VALIDO...RIPROVA\n");
        while(getchar() != '\n');  
        return 0;
    }
    getchar();  

    if (giorno < 1 || giorno > 31 || mese < 1 || mese > 12 || anno < 1900) {        //Controlla se la data inserita è ammessa

        printf("\nERRORE! LA DATA INSERITA NON E' VALIDA...\n");
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

    if(a->tempo_stimato < 1 || a->tempo_stimato > 10000) {       //Controlla se il valore inserito è ammesso

        printf("\nERRORE! IL VALORE INSERITO NON RIENTRA TRA QUELLI AMMESSI...\n");
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

    if(priorita < 1 || priorita > 3) {         //Verifica se il range della priorità inserita è ammesso

        printf("\nERRORE! DEVI INSERIRE UN VALORE DA 1 A 3...\n");
        return 0;
    }

    a->importanza = (Priorita)priorita;


    a->progresso = 0;     //Inizializza il progresso
    
    
    a->data_completamento[0] = '\0';     //Azzera la data di completamento

    
    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;     //Imposta lo stato dell'attività basandosi su una verifica della data

    printf("\nHAI AGGIUNTO L'ATTIVITA' CON SUCCESSO!\n");
    printf("===========================================\n\n");

    return 1;
}


/* ----------------------------------------------------------------

- Funzione: modifica_attivita

- Aggiorna i dati di un elemento di tipo 'Attivita' con nuovi valori forniti in input

- Specifica sintattica: void modifica_attivita(Attivita*) -> void

- Parametri:
            a: Attivita*

- Specifica semantica:  modifica_attivita(a) -> void

- Pre-Condizioni:  L'oggetto di tipo Attivita deve essere inizializzato

- Post-Condizioni: I valori dell'elemento vemgono aggiornati in base alle definizioni dei tipi

- Ritorna: (Nessun valore)

- Effetti collaterali: Modifica l'oggetto di tipo 'Attivita'

*/

void modifica_attivita(Attivita *a) {

    printf("===========================================\n");
    printf("    MODIFICA DELL'ATTIVITA' SELEZIONATA\n");
    printf("===========================================\n\n");

    
    printf("Nuova Descrizione    : ");
    fgets(a->descrizione, sizeof(a->descrizione), stdin);
    a->descrizione[strcspn(a->descrizione, "\n")] = '\0';


    printf("Nuovo Nome del Corso : ");
    fgets(a->corso, sizeof(a->corso), stdin);
    a->corso[strcspn(a->corso, "\n")] = '\0';


    printf("Nuova Data di Scadenza (GG/MM/AAAA): ");
    fgets(a->data_di_scadenza, sizeof(a->data_di_scadenza), stdin);
    a->data_di_scadenza[strcspn(a->data_di_scadenza, "\n")] = '\0';


    printf("Nuovo Tempo Stimato (ore): ");

     if (scanf("%d", &a->tempo_stimato) != 1) {
        printf("\nERRORE! VALORE INSERITO NON VALIDO...RIPROVA\n");
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

    a->stato = verifica_ritardo(a->data_di_scadenza) ? IN_RITARDO : IN_CORSO;     //Rivaluta lo stato dell'attività in base alla nuova data inserita

    printf("\nHAI MODIFICATO L'ATTIVITA' CON SUCCESSO!\n");
    printf("===========================================\n\n");
}


/* ----------------------------------------------------------------

- Funzione: verifica_ritardo

- Confronta una data la quale viene espressa come stringa nel formato "GG/MM/AAAA", con la data
  corrente per determinare se l'elemento è in ritardo

- Specifica sintattica:  int verifica_ritardo(const char*) -> int

- Parametri: 
             data_di_scadenza: const char*

-Specifica semantica:   verifica_ritardo(data_di_scadenza) -> int 

- Pre-Condizioni:  La stringa deve avere il seguente formato "GG/MM/AAAA"

- Post-Condizioni: Il confronto viene effettuato utilizzando esclusivamente il formato e i tipi

- Ritorna: 1 se la data inserita è antecedente la data corrente 
           0 altrimenti 

- Effetti collaterali: (Nessuno)

*/


int verifica_ritardo(const char *data_di_scadenza) {

    time_t t = time(NULL);

    struct tm *tm_corrente = localtime(&t);

    int giorno, mese, anno;
    sscanf(data_di_scadenza, "%d/%d/%d", &giorno, &mese, &anno);

    if (anno < tm_corrente->tm_year + 1900 ||    //Se l'anno della scadenza è minore dell'anno corrente l'attività è in ritardo

        (anno == tm_corrente->tm_year + 1900 && mese < tm_corrente->tm_mon + 1) ||   //Se l'anno coincide controlla il mese

        (anno == tm_corrente->tm_year + 1900 && mese == tm_corrente->tm_mon + 1 && giorno < tm_corrente->tm_mday)) {  //Se anno e mese coincidono controlla il giorno

        return 1;        //La scadenza è passata dunque l'attività è in ritardo
    }
    return 0;            //L'attività non è in ritardo
}


/* ----------------------------------------------------------------

- Funzione: mostra_attivita

- Visualizza in modo formattato i dati di un elemento di tipo 'Attivita'
  seguendo lo schema definito dai tipi

- Specifica sintattica: void mostra_attivita(const Attivita*) -> void

- Parametri: 
             a: const Attivita*

- Specifica semantica:   mostra_attivita(a) -> void    

- Pre-Condizioni:  Il puntatore deve fare riferimento a un oggetto di tipo 'Attivita'

- Post-Condizioni: I dati dell'elemento sono visualizzati secondo lo schema dei tipi

- Ritorna: (Nessun valore)

- Effetti collaterali: Stampa l'output a schermo

*/


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


/* ----------------------------------------------------------------

- Funzione: aggiorna_progresso_attivita

- Aggiorna il valore di avanzamento di un elemento di tipo Attivita, se raggiunge 100
  imposta lo stato a COMPLETATA e registra la data corrente

- Specifica sintattica:   void aggiorna_progresso_attivita(Attivita*) -> void

- Parametri: 
            a: Attivita*

- Specifica semantica:   aggiorna_progresso_attivita(a) -> void  

- Pre-Condizioni:  Il puntatore deve essere valido e il valore per il progresso deve essere
                   compreso tra 0 e 100

- Post-Condizioni:  Il campo del progresso viene aggiornato, se pari a 100 anche lo stato e
                    la data di completamento vengono modificati
                    
- Ritorna: (Nessun valore)

- Effetti collaterali: Modifica l'oggetto di tipo 'Attivita'

*/


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

        time_t adesso = time(NULL);      //Registra la data corrente come data di completamento

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
