//file.h 

#include "Coda_Priorità.h"

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
    Priorità importanza;                 //Priorità dell'attività (BASSA = 1; MEDIA = 2; ALTA = 3)
    Stato stato;                         //Stato dell'attività (IN RITARDO, IN CORSO, COMPLETATA)
}Attività;

//Prototipi delle funzioni

//Funzione che serve ad aggiungere/creare una nuova attività
void aggiungi_attività(PCoda c);

//Funzione che serve a modificare i parametri di un'attività esistente
void modifica_attività(PCoda c);

//Funzione che serve ad eliminare un'attività dalla coda
void elimina_attività(PCoda c);

//Funzione che serve a visualizzare il progresso delle attività
void visualizza_progresso(PCoda c);

//Funzione che permette di generare un report settimanale con riferimento allo stato dell'attività
void genera_report_settimanale(PCoda c);

//Funzione che serve a verificare se una determinata attività è in ritardo rispetto alla data di scadenza
int verifica_ritardo(const char* data_di_scadenza);
