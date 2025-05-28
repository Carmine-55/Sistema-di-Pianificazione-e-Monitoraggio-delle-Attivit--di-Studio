#ifndef TEST_PROGETTO_H
#define TEST_PROGETTO_H

extern FILE *fp_input;
extern FILE *fp_oracle;
extern FILE *fp_output;


/*FUNZIONI RELATIVE AL TESTING*/

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


void test_aggiungi_attivita(void);


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


void test_aggiorna_progresso(void);



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

void test_report_settimanale(void);

#endif
