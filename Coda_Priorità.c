#include <stdio.h>
#include <stdlib.h>
#include "Coda_Priorità.h"
#define MAX_HEAP 50              //Definizione della dimensione massima dell'heap

//Definizione della struttura per la coda a priorità
struct coda_P{
    Attività vet[MAX_HEAP];      //Array di attività memorizzati nell'heap
    int num_elementi;            //Numero attuale di elementi nell'heap
};

//Funzione per creare una nuova di coda priorità
PCoda nuova_PC(void){
    PCoda c;
    c = malloc(sizeof(struct coda_P));            //Allocazione della memoria per la coda 
    if (c == NULL)
    return NULL;
    c->num_elementi = 0;                          //Inizializzazione del numero di elementi a zero
    return c;                                     //Ritorno del puntatore alla coda 
}

int vuota_PC(PCoda c){
    if(!c)                                        //Controlla se il puntatore è NULL
    return 1;
    return c->num_elementi == 0;                  //Ritorna vero se la coda non ha elementi(quindi è vuota)
}

// Funzione per ottenere il massimo elemento dalla coda di priorità
Attività ottieni_max(PCoda c){
    if(!c || c->num_elementi == 0){
        printf("Errore! La coda è vuota.\n ");
        return -1;
    }
    return c->vet[1];                              // Restituisce l'attività con priorità più alta, quindi ritorna l'elemento al primo indice (massimo in un max-heap)
}

// Funzione per eliminare l'elemento massimo dalla coda di priorità
int cancella_max(PCoda c){
    if(!c){
    printf("Errore! La coda non esiste.\n ");
    return -1;
    }
    if(c->num_elementi == 0){
        printf("Errore! Nessuna attività da rimuovere.");
        return 0;
    }
    c->vet[1] = c->vet[c->num_elementi];           //Sostituisce la radice con l'ultimo elemento
    c->num_elementi--;                             //Decrementa il numero degli elementi
    scendi(c);
    return 1;
}

// Funzione per inserire un nuovo elemento nell'heap.
int inserisci(PCoda c, Attività nuovaAttività){
    if(!c){
    printf("Errore! La coda non esiste.\n");
    return -1;
    }
    if(c->num_elementi == MAX_HEAP){
    printf("Errore! Impossibile inserire altre attività.\n");
    return 0;
    }
    c->num_elementi++;                             //Incrementa il numero di elementi
    c->vet[c->num_elementi] = nuovaAttività;       //Inserisce il nuovo elemento all'ultima posizione
    sali(c);                                       //Riaggiusta l'heap risalendo l'elemento inserito
    return 1;                                      //Inserimento riuscito
}

// Funzione per riaggiustare l'heap verso l'alto
static void sali(PCoda c){
    int pos = c->num_elementi, i = pos/2;
    Attività temp;

    while(pos < 1)
    {
     // Se l'elemento inserito ha priorità maggiore del suo genitore, scambia i loro valori
        if(c->vet[pos].priorità > c->vet[i].priorità){
        temp = c->vet[i];
        c->vet[i] = c->vet[pos];
        c->vet[pos] = temp;
        pos = i;
        i = pos / 2;                                //Continua a risalire nell'heap
        }   else
              break;                                //Se non sono necessari altri scambi termina
    }
}

//Funzione per riaggiustare l'heap verso il basso
static void scendi(PCoda c){
    int n = c->num_elementi, pos, i = 1;
    Attività temp;

    while(1)
    {
       // Determina la posizione del figlio con priorità più alta

       if(2*i + 1 <= n)                             //Se il nodo corrente ha due figli
          pos = (c->vet[2*i].priorità > c->vet[2*i + 1].priorità) ? 2*i : 2*i + 1;
       else if (2*i <= n)                           //Se il nodo corrente ha un solo figlio
          pos = 2*i;
          else
                    break;                          //Se non ha figli interrompe il ciclo 

      // Scambia i valori se il nodo figlio ha una priorità più alta rispetto al nodo genitore       
        if (c->vet[pos].priorità > c->vet[i].priorità)
        {
             temp = c->vet[i];
             c->vet[i] = c->vet[pos];
             c->vet[pos] = temp;
             i = pos;                               // Continua a scendere nell'heap.
       }
       else
           break;                                   // Termina se non sono necessari altri scambi.
     }
}