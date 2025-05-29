#ifndef FUNZIONI_FILE_H
#define FUNZIONI_FILE_H

#include "coda_priorita.h"



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


int salvataggio_su_file(const char *nome_file, PCoda c);



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


int caricamento_da_file(const char *nome_file, PCoda c);

#endif
