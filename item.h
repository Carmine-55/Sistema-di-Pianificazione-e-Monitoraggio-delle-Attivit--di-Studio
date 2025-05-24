#ifndef ITEM_H
#define ITEM_H

typedef enum {
     BASSA = 1,
     MEDIA = 2,
     ALTA = 3 
    } Priorita;

typedef enum {
     IN_CORSO,
     COMPLETATA,
     IN_RITARDO 
    } Stato;

typedef struct {
    char descrizione[100];          //Descrizione dell'attività (max 100 caratteri)
    char corso[50];                 //Nome del corso o materia (max 50 caratteri)
    char data_di_scadenza[11];      //Data di scadenza nel formato "GG/MM/AAAA"
    int tempo_stimato;              //Tempo stimato (in ore) per completare l'attività
    Priorita importanza;            //Livello di importanza (BASSA, MEDIA o ALTA)
    Stato stato;                    //Stato (IN_CORSO, COMPLETATA o IN_RITARDO)
    int progresso;                  //Percentuale di completamento (0-100)
    char data_completamento[16];    //Il formato sarà sempre GG/MM/AAAA
} Attivita;

/* FUNZIONE RELATIVE ALLE ATTIVITA' */

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

int aggiungi_attivita(Attivita *a);


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

- Effetti collaterali: Modifica l'oggetto di tipo Attivita

*/

void modifica_attivita(Attivita *a);


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

int verifica_ritardo(const char *data_di_scadenza);


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

void mostra_attivita(const Attivita *a);


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

void aggiorna_progresso_attivita(Attivita *a);

#endif
