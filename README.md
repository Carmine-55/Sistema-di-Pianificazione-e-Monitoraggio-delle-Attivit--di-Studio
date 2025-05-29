# Gestione attività di studio - Sistema di pianificazione delle attività

## Descrizione del programma
Il progetto **Gestione attività di studio** è un sistema sviluppato interamente in linguaggio C, il cui scopo principale è la gestione delle attività di studio. L’applicazione permette di inserire, modificare, eliminare e aggiornare il progresso delle attività, oltre a generare report settimanali e notificare le attività in ritardo. Inoltre per garantire una gestione efficiente, il sistema sfrutta una coda di priorità implementata come max-heap, la quale organizza le attività in base al loro livello di importanza **(Priorità)**

## Caratteristiche 

* **Gestione delle attività**: 
 1. Inserimento di nuove attività con raccolta dati quali descrizione, nome del corso, data di scadenza, tempo stimato, priorità e stato
 2. Modifica dei dati di un'attività esistente
 3. Eliminazione delle attività selezionate (In base alla descrizione)

* **Monitoraggio e Aggiornamento del progresso**:
 1. Aggiornamento dinamico del progresso (in percentuale) per ogni attività
 2. Modifica automatica dello stato dell’attività (IN RITARDO, IN CORSO, COMPLETATA) in base alla data di scadenza e al progresso

* **Reportistica e notifiche**:
 1. Generazione di report settimanali con riepilogo delle attività completate, in corso e in ritardo
 2. Visualizzazione di notifiche per le attività in ritardo

* **Permanenza dei dati**
 1. Salvataggio su file di testo delle attività, tramite un formato strutturato (intestazioni e separatori) per garantire una facile consultazione
 2. Caricamento dei dati salvati solo nel momento dell’avvio dell’applicazione

* **Interfaccia**:
 1. Menù interattivo che rende molto semplice l'utilizzo del sistema


## Sistema di utilizzo

* **Avvio dell’applicazione**:

1. Al lancio, il programma tenta di caricare le attività salvate da un file (attivita'.txt). Se il file non esiste o il caricamento fallisce, viene creato un nuovo file di salvataggio
2. L’utente viene guidato attraverso una schermata iniziale che, tramite la funzione pulisci_schermo(), garantisce un’interfaccia ordinata

* **Menù principale**:

 Dopo il caricamento, il menù principale presenta le seguenti opzioni:

**1. Aggiungi Attività**:
* Inserisci i dati richiesti (descrizione, nome del corso, data di scadenza, tempo stimato, priorità)
* Il sistema determina automaticamente lo stato dell’attività confrontando la data di scadenza con la data corrente

**2. Modifica Attività**:
* Inserisci l’indice dell’attività da modificare
* Aggiorna i dati desiderati (descrizione, corso, data di scadenza, tempo stimato, priorità)

**3. Elimina Attività**:
* Rimuove un'attività in base alla descrizione fornita
* La struttura dati viene aggiornata per mantenere la proprietà del max-heap

**4. Aggiorna Progresso dell’attività**:
* Seleziona l’attività tramite indice e inserisci la nuova percentuale di progresso (da 0 a 100)
* Se il progresso raggiunge il 100%, lo stato viene automaticamente impostato a COMPLETATA e viene registrata la data di completamento

**5. Visualizza Progresso**:
*Mostra un riepilogo dettagliato di tutte le attività, inclusi descrizione, corso, scadenza, tempo stimato, priorità, stato e progresso

**6. Genera Report Settimanale**:
* Il sistema elabora le attività in base alla data e genera un report che suddivide le attività in COMPLETATE, IN CORSO e IN RITARDO, fornendo un riepilogo settimanale

**7. Ottieni l’attività con massima priorità**:
* Visualizza l’attività in cima alla coda (ossia quella con il maggior grado di importanza)

**8. Mostra notifiche delle attività in ritardo**:
* Evidenzia in output le attività che sono in ritardo rispetto alla data di scadenza

**9. Uscita dal programma**:
* Chiude l’applicazione dopo aver salvato tutte le modifiche su file



## Struttura del progetto

Il progetto è stato organizzato in moduli per mantenere il codice modulare e facilmente manutenibile:

* **attivita.h/.c** Definizione della struttura 'Attivita' e degli enumeratori per 'Priorità' e 'Stato'

* **coda_priorita.h/.c** Implementazione della coda di priorità (max-heap) la quale gestisce l’ordinamento delle attività

* **funzioni_file.h/.c** Funzioni per il salvataggio e il caricamento delle attività da file

## Utilizzo

1. Copia il link della repository
2. Compila il progetto con i makefile forniti
3. Usufruisci del programma

## Autori 

Il progetto è stato interamente sviluppato da **CarmineSaggese**

**Avviso⚠️**: Per conoscere i dettagli e le implementazioni, consultare le documentazioni e i file sorgente forniti nella repository.
