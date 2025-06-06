#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funzioni_file.h"
#include "coda_priorita.h"
#include "attivita.h"


/* FUNZIONI RELATIVE AI FILE */

/* ----------------------------------------------------------------

- Funzione: salvataggio_su_file

- Salva gli elementi di tipo 'Attivita' in un file di testo usando un formato fisso,
  comprensivo di intestazione e separatori

- Specifica sintattica:  int salvataggio_su_file(const char*, PCoda) -> int

- Parametri: 
            nome_file: attività.txt 
            c: PCoda

- Specifica semantica:  salvataggio_su_file(nome_file, c) -> int 

- Pre-Condizioni: Il file, se è presente, deve corrispondere al formato stabilito 

- Post-Condizioni: I dati vengono scritti su disco in base al formato stabilito

- Ritorna: 1 se il salvataggio è avvenuto con successo
           0 altrimenti

- Effetti collaterali: Crea oppure sovrascrive il file sul disco           


*/



int salvataggio_su_file(const char *nome_file, PCoda c) {

    FILE *file = fopen(nome_file, "w");

    if (!file) {

        perror("ERRORE DURANTE L'APERTURA DEL FILE DI SALVATAGGIO!");

        return 0;
    }


    fprintf(file, "===========================================\n");
    fprintf(file, "          Elenco Attivita'\n");
    fprintf(file, "===========================================\n\n");


    int n = ottieni_numero_attivita(c);     //Ottiene il numero totale di attività presenti nella coda

    for (int i = 1; i <= n; i++) {

         Attivita a = ottieni_attivita(c, i);

         fprintf(file, "Attività %d\n", i);

         fprintf(file, "Descrizione    : %s\n", a.descrizione);

         fprintf(file, "Corso          : %s\n", a.corso);

         fprintf(file, "Scadenza       : %s\n", a.data_di_scadenza);

         fprintf(file, "Tempo stimato  : %d ore\n", a.tempo_stimato);

         fprintf(file, "Priorita'      : %s\n",  (a.importanza == ALTA) ? "ALTA" : (a.importanza == MEDIA) ? "MEDIA" : "BASSA");

         fprintf(file, "Stato          : %s\n", (a.stato == IN_RITARDO) ? "In Ritardo" : (a.stato == COMPLETATA) ? "Completata" : "In Corso");

         fprintf(file, "Progresso      : %d%%\n", a.progresso);      //Stampa il progresso nell'attività come percentuale


        //Verifica se è disponibile una data di completamento, in caso contrario, stampa un valore di default 

         fprintf(file, "Data Completamento : %s\n", (a.data_completamento[0] ? a.data_completamento : "Non disponibile"));

         fprintf(file, "-------------------------------------------\n\n");
    }
    fclose(file);

    return 1;
}



/* ----------------------------------------------------------------

- Funzione: caricamento_da_file

- Carica gli elementi di tipo Attivita da un file di testo e li inserisce in una struttura
  di tipo PCoda, basandosi su un formato stabilito

- Specifica sintattica:  int caricamento_da_file(const char*, PCoda) -> int

- Parametri: 
             nome_file: attività.txt 
             c: PCoda

- Specifica semantica:  caricamento_da_file(nome_file, c) -> int    

- Pre-Condizioni:  Il file esiste ed è formattato secondo lo schema previsto

- Post-Condizioni: La struttura PCoda viene popolata con gli elementi letti dal file

- Ritorna: 1 se il caricamento ha avuto successo
           0 altrimenti

- Effetti collaterali: Modifica la struttura di tipo CodaPriorita        

*/


int caricamento_da_file(const char *nome_file, PCoda c) {

    FILE *file = fopen(nome_file, "r");

    if (!file) {

        return 0;
    }

    char buffer[256];        //Buffer che serve a leggere le righe dal file

    Attivita a;


    //Leggo e ignoro le prime tre righe del file

    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {

        if (buffer[0] == '-' || strlen(buffer) <= 1)        //Se la riga corrente è un separatore o è troppo corta, la salta per non leggerla come dato utile
            continue;

        
        fgets(buffer, sizeof(buffer), file);
        strcpy(a.descrizione, buffer + 17);
        a.descrizione[strcspn(a.descrizione, "\n")] = '\0';         //Rimuove il carattere di newline in eccesso per pulire la stringa

       
        fgets(buffer, sizeof(buffer), file);
        strcpy(a.corso, buffer + 17);
        a.corso[strcspn(a.corso, "\n")] = '\0';

       
        fgets(buffer, sizeof(buffer), file);
        strcpy(a.data_di_scadenza, buffer + 17);
        a.data_di_scadenza[strcspn(a.data_di_scadenza, "\n")] = '\0';

        
        fgets(buffer, sizeof(buffer), file);     //Legge il "Tempo stimato" come stringa
        a.tempo_stimato = atoi(buffer + 17);     //Lo converte in intero

       
        fgets(buffer, sizeof(buffer), file);
        if (strcmp(buffer + 17, "ALTA\n") == 0)
            a.importanza = ALTA;

        else if (strcmp(buffer + 17, "MEDIA\n") == 0)
            a.importanza = MEDIA;

        else
            a.importanza = BASSA;

       
        fgets(buffer, sizeof(buffer), file);

        if (strcmp(buffer + 17, "In Ritardo\n") == 0)
            a.stato = IN_RITARDO;

        else if (strcmp(buffer + 17, "Completata\n") == 0)
            a.stato = COMPLETATA;

        else
            a.stato = IN_CORSO;

       
        fgets(buffer, sizeof(buffer), file);

        int prog;

        sscanf(buffer + 17, "%d", &prog);

        a.progresso = prog;

       
        fgets(buffer, sizeof(buffer), file);



        //Se la riga contiene più di 21 caratteri, copio il valore, altrimenti, imposto il campo a "Non disponibile"

        if(strlen(buffer) > 21) {

            strcpy(a.data_completamento, buffer + 21);

            a.data_completamento[strcspn(a.data_completamento, "\n")] = '\0';

        } else {

            strcpy(a.data_completamento, "Non disponibile");
        }

        inserisci(c, a);
    }
    fclose(file);

    return 1;
}
