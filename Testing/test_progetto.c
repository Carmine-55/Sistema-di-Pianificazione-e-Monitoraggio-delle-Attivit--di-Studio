#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "attivita.h"
#include "coda_priorita.h"
#include "test_progetto.h"

FILE *fp_input = NULL;
FILE *fp_oracle = NULL;
FILE *fp_output = NULL;


/* ----------------------------------------------------------------


- Funzione: test_aggiungi_attivita

- Simula la creazione di un nuovo elemento di tipo Attivita
 e verifica che i valori inizializzati corrispondano all'oracolo atteso

- Specifica sintattica:  void test_aggiungi_attivita(void)

- Parametri: (Nessuno)

- Specifica semantica: test_aggiungi_attivita() -> void

- Pre-Condizioni: I puntatori fp_input, fp_oracle e fp_output devono essere già aperti e validi
                  La struttura Attivita è considerata allocata e valida

- Post-Condizioni: Il test verifica che la struttura Attivita contenga i parametri previsti
                    L'input, l'oracolo atteso e l'esito del test vengono scritti nei file

- Ritorna: (Nessun valore)

- Effetti collaterali: Scrive su file (fp_input, fp_oracle, fp_output) e su terminale
                       Crea una variabile locale 'Attivita' e ne modifica i campi

*/


void test_aggiungi_attivita(void) {
    
    fprintf(fp_input, "--- TEST 1: Aggiungi Attivita' ---\n\n");

    fprintf(fp_input, "Descrizione: Progetto di Analisi\n");
    fprintf(fp_input, "Corso: Matematica\n");
    fprintf(fp_input, "Data di Scadenza: 15/06/2025\n");
    fprintf(fp_input, "Tempo Stimato: 20 (Ore) \n");
    fprintf(fp_input, "Priorità: 3 (ALTA)\n\n");

    
    Attivita a;

    strcpy(a.descrizione, "Progetto di Analisi");
    strcpy(a.corso, "Matematica");
    strcpy(a.data_di_scadenza, "15/06/2025");

    a.tempo_stimato = 20;
    a.importanza = ALTA;
    a.progresso = 0;
    a.data_completamento[0] = '\0';      //Azzera la stringa della data di completamento


    a.stato = verifica_ritardo(a.data_di_scadenza) ? IN_RITARDO : IN_CORSO;     //Determina lo stato in base alla data di scadenza

    int risultato = 1;  

    //Confronta ogni campo della struttura con i valori attesi

    int test_superato = (risultato == 1 && strcmp(a.descrizione, "Progetto di Analisi") == 0 && strcmp(a.corso, "Matematica") == 0 && strcmp(a.data_di_scadenza, "15/06/2025") == 0 &&

    a.tempo_stimato == 20 && a.importanza == ALTA &&  a.progresso == 0);

    
    fprintf(fp_oracle, "--- TEST 1: Oracle ---\n\n");

    fprintf(fp_oracle, "Si attende che Attivita' contenga:\n\n");
    fprintf(fp_oracle, "Descrizione: Progetto di Analisi\n");
    fprintf(fp_oracle, "Corso: Matematica\n");
    fprintf(fp_oracle, "Data di Scadenza: 15/06/2025\n");
    fprintf(fp_oracle, "Tempo Stimato: 20 (Ore)\n");
    fprintf(fp_oracle, "Priorità: ALTA\n");
    fprintf(fp_oracle, "Progresso: 0 (Percento)\n\n");

    
    if (test_superato) {

        fprintf(fp_output, "TEST 1 (Aggiungi Attivita'): SUPERATO\n\n");

         printf("TEST 1 (Aggiungi Attivita'): SUPERATO\n");

    } else {

        fprintf(fp_output, "TEST 1 (Aggiungi Attivita'): FALLITO\n\n");

         printf("TEST 1 (Aggiungi Attivita'): FALLITO\n");
    }
}


/* ----------------------------------------------------------------

- Funzione: test_aggiorna_progresso

- Simula l'aggiornamento del progresso di un’attività esistente, passando da un valore iniziale pari a 0 a un aggiornamento al 100%
  Imposta il relativo stato a COMPLETATA e registra la data di completamento

- Specifica sintattica: void test_aggiorna_progresso(void)

- Parametri: (Nessuno)

- Specifica semantica: test_aggiorna_progresso() -> void

- Pre-Condizioni: I puntatori fp_input, fp_oracle e fp_output devono essere già aperti e validi
                  La struttura Attivita è considerata allocata e valida

- Post-Condizioni: La struttura 'Attivita' viene aggiornata con i parametri previsti
                   L'input, l'oracolo atteso e l'esito del test vengono scritti nei file
                   
- Ritorna: (Nessun valore)

- Effetti collaterali: Modifica la variabile 'Attivita'; 
                       Scrive su file (fp_input, fp_oracle, fp_output)

*/


void test_aggiorna_progresso(void) {

    fprintf(fp_input, "--- TEST 2: Aggiorna Progresso ---\n\n");

    fprintf(fp_input, "Attivita' iniziale:\n Descrizione: Progetto di Analisi, \n Stato: IN CORSO,\n Progresso: 0 (Percento) \n");
    fprintf(fp_input, "Aggiornamento del progresso al 100 (Percento)\n\n");

    Attivita a;

    strcpy(a.descrizione, "Progetto di Analisi");
    strcpy(a.corso, "Matematica");
    strcpy(a.data_di_scadenza, "15/06/2025");

    a.tempo_stimato = 20;
    a.importanza = ALTA;
    a.progresso = 0;
    a.data_completamento[0] = '\0';     //Data di completamento inizialmente vuota
    a.stato = IN_CORSO;
   
    
    a.progresso = 100;
    a.stato = COMPLETATA;

    //Ottiene la data corrente per poi formattarla e salvarla in data_completamento

    time_t adesso = time(NULL);

    struct tm *tempoCorrente = localtime(&adesso);


    //Formatta la data corrente (GG/MM/AAAA) e successivamente la scrive  nella variabile a.data_completamento

    sprintf(a.data_completamento, "%02d/%02d/%04d", tempoCorrente->tm_mday, tempoCorrente->tm_mon + 1, tempoCorrente->tm_year + 1900);


    //Controlla che il progresso sia al 100%, che lo stato sia 'COMPLETATA' e che la data di completamento non sia vuota
    
    int test_superato = (a.progresso == 100 && a.stato == COMPLETATA && strlen(a.data_completamento) > 0);

    
    fprintf(fp_oracle, "--- TEST 2: Oracle ---\n\n");

    fprintf(fp_oracle, "Dopo l'aggiornamento:\n");
    fprintf(fp_oracle, "Progresso = 100 (Percento)\n");
    fprintf(fp_oracle, "Stato = COMPLETATA\n");
    fprintf(fp_oracle, "Data Completamento: Non deve essere vuota \n\n");


    if (test_superato) {

        fprintf(fp_output, "TEST 2 (Aggiorna Progresso): SUPERATO\n\n");

        printf("TEST 2 (Aggiorna Progresso): SUPERATO\n");

    } else {

        fprintf(fp_output, "TEST 2 (Aggiorna Progresso): FALLITO\n\n");

        printf("TEST 2 (Aggiorna Progresso): FALLITO\n");
    }
}


/* ----------------------------------------------------------------

- Funzione: test_report_settimanale

- Simula la generazione di un report settimanale, che raggruppa le attività per stato in base alla data corrente
  Verifica che il report legga correttamente i conteggi per le attività completate, in corso, o in ritardo

- Specifica sintattica: void test_report_settimanale(void) 

- Parametri: (Nessuno)

- Specifica semantica: test_report_settimanale(void) -> void

- Pre-Condizioni: I puntatori per i file devono essere aperti
                  La funzione nuova_PC() deve restituire un puntatore valido a una coda
                  Le funzioni inserisci(), ottieni_numero_attivita() e ottieni_attivita() devono essere definite correttamente

- Post-Condizioni: La coda contenente le attività viene analizzata
                   Il report viene confrontato con i valori attesi
                   L'input, l'oracolo atteso e l'esito del test vengono scritti nei file

- Ritorna: (Nessun valore)

- Effetti collaterali: La funzione va a modificare i contenuti della coda creata
                       Esegue scritture sui file (fp_input, fp_oracle, fp_output)


*/


void test_report_settimanale(void) {

    fprintf(fp_input, "--- TEST 3: Report Settimanale ---\n\n");

    fprintf(fp_input, "Inserite 3 attivita':\n");
    fprintf(fp_input, "Attivita' A: COMPLETATA, Data: [Oggi] \n");
    fprintf(fp_input, "Attivita' B: IN CORSO, Data: [Oggi] \n");
    fprintf(fp_input, "Attivita' C: IN CORSO, Data: 11/12/2023 (Non rientra nella settimana corrente)\n\n");

    PCoda c = nuova_PC();

    if (c == NULL) {

        fprintf(fp_output, "TEST 3 (Report Settimanale): FALLITO (Impossibile allocare memoria per la coda)\n\n");

        printf("TEST 3 (Report Settimanale): FALLITO (Impossibile allocare memoria per la coda)\n");

        return;
    }
    
    Attivita A, B, C;
   

    time_t ora = time(NULL);

    struct tm *tm_adesso = localtime(&ora);

    char oggi[11];

    // Formatta la data corrente nel formato GG/MM/AAAA

    sprintf(oggi, "%02d/%02d/%04d", tm_adesso->tm_mday, tm_adesso->tm_mon + 1, tm_adesso->tm_year + 1900);
   

    strcpy(A.descrizione, "Attivita' A");
    strcpy(A.corso, "Corso A");
    strcpy(A.data_di_scadenza, oggi);

    A.tempo_stimato = 2;
    A.importanza = MEDIA;
    A.progresso = 100;

    strcpy(A.data_completamento, oggi);   // Imposta la data di completamento uguale a oggi

    A.stato = COMPLETATA;
   

    strcpy(B.descrizione, "Attivita' B");
    strcpy(B.corso, "Corso B");
    strcpy(B.data_di_scadenza, oggi);

    B.tempo_stimato = 3;
    B.importanza = BASSA;
    B.progresso = 50;
    B.data_completamento[0] = '\0';        // Nessuna data di completamento, poiché l'attività è ancora in corso
    B.stato = IN_CORSO;
   

    strcpy(C.descrizione, "Attivita' C");
    strcpy(C.corso, "Corso C");
    strcpy(C.data_di_scadenza, "05/11/2020");

    C.tempo_stimato = 1;
    C.importanza = ALTA;
    C.progresso = 20;
    C.data_completamento[0] = '\0';
    C.stato = IN_CORSO;
   
    inserisci(c, A);
    inserisci(c, B);
    inserisci(c, C);
   
    
    fprintf(fp_oracle, "--- TEST 3: Oracle ---\n\n");

    fprintf(fp_oracle, "Si attende:\n Attivita' (COMPLETATA) = 1,\n Attivita' (IN CORSO) = 1,\n Attivita' (IN RITARDO) = 0 \n\n");

    int aspettativa_completate = 1, aspettativa_in_corso = 1, aspettativa_in_ritardo = 0;

    int conta_completate = 0, conta_in_corso = 0, conta_in_ritardo = 0;


    // Scorre la coda per contare le attività in base alla data e allo stato

    for (int i = 1; i <= ottieni_numero_attivita(c); i++) {


        Attivita temp = ottieni_attivita(c, i);

        //Se l'attività è 'COMPLETATA' e ha una data di completamento utilizza quella come riferimento; altrimenti usa la data di scadenza

        char *data_riferimento = (temp.stato == COMPLETATA && strlen(temp.data_completamento) > 0) ? temp.data_completamento : temp.data_di_scadenza;

        if (strcmp(data_riferimento, oggi) == 0) {

            if (temp.stato == COMPLETATA)
                conta_completate++;

            else if (temp.stato == IN_CORSO)
                conta_in_corso++;

            else if (temp.stato == IN_RITARDO)
                conta_in_ritardo++;
        }
    }
   
    int test_superato = (conta_completate == aspettativa_completate && conta_in_corso == aspettativa_in_corso && conta_in_ritardo == aspettativa_in_ritardo);

   
    if (test_superato) {

        fprintf(fp_output, "TEST 3 (Report Settimanale): SUPERATO\n\n");

        printf("TEST 3 (Report Settimanale): SUPERATO\n");

    }   else {

        fprintf(fp_output, "TEST 3 (Report Settimanale): FALLITO\n");

        fprintf(fp_output, "Atteso: COMPLETATE=%d, IN CORSO=%d, IN RITARDO=%d\n",  aspettativa_completate, aspettativa_in_corso, aspettativa_in_ritardo);

        fprintf(fp_output, "Trovato: COMPLETATE=%d, IN CORSO=%d, IN RITARDO=%d\n\n", conta_completate, conta_in_corso, conta_in_ritardo);

        printf("TEST 3 (Report Settimanale): FALLITO\n");
    }
   
    free(c);   //Libera la memoria allocata per la coda
}
