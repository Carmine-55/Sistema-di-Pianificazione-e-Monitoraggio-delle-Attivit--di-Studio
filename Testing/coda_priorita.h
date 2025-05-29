#ifndef CODA_PRIORITA_H
#define CODA_PRIORITA_H

#include "attivita.h"

typedef struct CodaPriorita CodaPriorita;
typedef CodaPriorita* PCoda;



/* FUNZIONI RELATIVE ALLA CODA A PRIORITA' */

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

PCoda nuova_PC(void);




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



int vuota_PC(PCoda c);



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

int inserisci(PCoda c, Attivita nuovaAttivita);



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



Attivita ottieni_max(PCoda c);


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


void mostra_progresso(PCoda c);



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



void genera_report_settimanale(PCoda c);



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



void elimina_attivita(PCoda c);



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


void mostra_notifiche(PCoda c);



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


int ottieni_numero_attivita(PCoda c);


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


Attivita ottieni_attivita(PCoda c, int indice);


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


Attivita* ottieni_attivita_puntatore(PCoda c, int indice);


#endif

