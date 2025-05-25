--- ADT CODA CODA A PRIORITA' ---

typedef struct {
    Vettore:              Array di 'Attivita    // Array di attività memorizzate nell'heap
    Numero di elementi:   Intero                // Numero di elementi nella coda
} CodaPriorita, *PCoda;



--- FUNZIONI RELATIVE ALLA CODA A PRIORITA' ---

- nuova_PC() -> PCoda                                       Crea e inizializza dinamicamente una nuova coda a priorità.

- inserisci(PCoda c, Attivita nuovaAttivita) -> int         Inserisce una nuova attività nella coda, mantenendo le proprietà del max-heap basate sull’importanza (priorità) 

- ottieni_max(PCoda c) -> Attivita                          Restituisce l’attività con la più alta priorità, quella situata in cima al max-heap

- elimina_attivita(PCoda c) -> void                         Rimuove un'attività dalla coda in base alla descrizione fornita dall’utente, aggiornando l’ordinamento del max-heap

- mostra_progresso(PCoda c) -> void                         Visualizza in output lo stato di avanzamento di tutte le attività presenti nella coda

- genera_report_settimanale(PCoda c) -> void                Genera un report settimanale analizzando le attività che rientrano nel range della settimana corrente

- mostra_notifiche(PCoda c) -> void                         Visualizza le notifiche relative alle attività in ritardo





--- ADT ATTIVITA' ---

typedef struct {

    Descrizione          : Stringa 
    Corso                : Stringa 
    Data di Scadenza     : Stringa (Formato GG/MM/AAAA)
    Tempo Stimato        : Intero
    Importanza           : Enumumerazione Priorita (BASSA = 1, MEDIA = 2, ALTA = 3)
    Stato                : Enumerazione Stato (IN_RITARDO, IN_CORSO, COMPLETATA)
    Progresso            : Intero (Percentuale da 0 a 100)
    Data Completamento   : Stringa (Formato GG/MM/AAAA)
    
}Attivita; 



--- FUNZIONE RELATIVE AD ATTIVITA' ---

aggiungi_attivita(Attivita *a) -> int                   Raccoglie in input i dati necessari per creare una nuova attività, inizializza il progresso a 0 e determina lo stato (IN_CORSO o IN_RITARDO) in base al confronto della data di scadenza con la data corrente

modifica_attivita(Attivita *a) -> void                  Permette di aggiornare i dati di una attività esistente, compresa la rivalutazione del suo stato in base a una nuova data di scadenza

verifica_ritardo(const char *data_di_scadenza) -> int   Confronta la data di scadenza (formattata come "GG/MM/AAAA") con la data corrente per determinare se l’attività è in ritardo. Restituisce 1 se la data è antecedente a quella corrente, 0 altrimenti

mostra_attivita(const Attivita *a) -> void              Visualizza in modo formattato tutti i dati relativi a un’attività, incluse le informazioni di avanzamento e di completamento, se disponibili

aggiorna_progresso_attivita(Attivita *a) -> void        Aggiorna la percentuale di completamento di un’attività. Se il progresso raggiunge il 100%, l’attività viene contrassegnata come COMPLETATA e viene registrata la data di completamento corrente



--- FUNZIONI RELATIVE AI FILE ---

salvataggio_su_file(const char *nome_file, PCoda c) -> int         Salva l’elenco delle attività su un file di testo (il file viene creato o sovrascritto) usando un formato fisso

caricamento_da_file(const char *nome_file, PCoda c) -> int         Carica le attività da un file di testo formattato secondo lo schema prestabilito e popola la coda a priorità



--- FUNZIONI RELATIVE ALL'INTERFACCIA UTENTE --- 

- pulisci_schermo() -> void                             Pulisce il terminale utilizzando i comandi di sistema appropriati (cls per Windows, clear per Mac/Linux)




--- PSEUDOCODICE --- 

- All'avvio:
1. Il programma tenta di caricare le attività dal file esterno ("attivita'.txt")
2. Se il caricamento fallisce, visualizzi un messaggio d'errore e viene creato un nuovo file di salvataggio

- Apertura del menù principale:

-Scelte disponibili nel menù (implementate tramite uno switch):

1. Aggiungi Attività
2. Modifica Attività
3. Elimina Attività
4. Aggiorna il progresso dell’attività
5. Visualizza il progresso delle attività
6. Genera report settimanale
7. Ottieni l’attività con massima priorità
8. Mostra le notifiche delle attività in ritardo
9. Uscita dal programma


Case 1: (Aggiungi attività)

-Chiedi all'utente di inserire: 

- Descrizione (Stringa, max 100 caratteri)
- Nome del corso (Stringa, max 50 caratteri)
- Data di scadenza (Stringa, formato "GG/MM/AAAA")
- Tempo Stimato (Intero, in ore)
- Priorità (Intero: 1 = BASSA, 2 = MEDIA, 3 = ALTA)

- Verifica l’input (controlla i campi vuoti, il formato data, il range di valori), se errati stampa messaggio d'errore
- Imposta il progresso a 0
- Utilizza la funzione verifica_ritardo per determinare lo stato (IN_CORSO oppure IN_RITARDO) confrontando la data di scadenza con quella corrente
- Inserisci la nuova attività nella coda a priorità
- Salva la coda aggiornata sul file esterno
- Visualizza un messaggio di conferma
- Se premi INVIO torna al menù principale 


Case 2: (Modifica attività)

- Se non sono presenti attività, mostra un messaggio d’avviso. Se premi INVIO ritorna al menù principale
- Altrimenti chiedi all'utente di inserire l’indice dell’attività che vuole modificare

- Richiedi i nuovi dati per:
  
- Descrizione
- Nome del corso
- Data di Scadenza (Formato "GG/MM/AAAA")
- Tempo Stimato    (In ore)
- Priorità         (Intero: 1 = BASSA, 2 = MEDIA, 3 = ALTA)

- Rivaluta lo stato dell'attività in base alla nuova data inserita
- Aggiorna l’attività selezionata nella coda
- Salva le modifiche sul file esterno
- Premi INVIO per tornare al menù principale


Case 3: (Elimina attività)

- Se la coda è vuota, visualizza un messaggio d’errore
- Altrimenti, chiedi all'utente di fornire la descrizione dell’attività da eliminare
- Rimuovi l’attività corrispondente dalla coda a priorità (aggiornando il max-heap)
- Salva la coda modificata sul file esterno
- Premi INVIO e torna al menù principale


Case 4: (Aggiorna il progresso)

- Se non ci sono attività, visualizza un messaggio d’avviso
- Altrimenti, chiedi all'utente di inserire l’indice dell’attività che vuole aggiornare
- Richiedi la nuova percentuale di progresso (da 0 a 100)
- Se il progresso raggiunge 100, imposta lo stato a COMPLETATA e registra la data corrente come data di completamento
- Aggiorna il progresso nella struttura dell’attività
- Salva la coda aggiornata sul file esterno
- Premi INVIO e torna al menù principale


Case 5: (Visualizza progresso)

- Stampa a schermo tutte le attività presenti nella coda, mostrando per ciascuna:

- Descrizione 
- Corso
- Data di Scadenza (formato GG/MM/AAAA) 
- Tempo Stimato    (In ore)
- Priorità         (1 = BASSA, 2 = MEDIA, 3 = ALTA)
- Stato            (IN_RITARDO, IN_CORSO, COMPLETATA)
- Progresso        (0 a 100)
- Data di Completamento  (Solo se presente)


Case 6: (Genera report settimanale)

- Analizza le attività nella coda per identificare quelle che rientrano nella settimana corrente (da lunedì a domenica)
- Genera e visualizza un report riepilogativo che includa il conteggio delle attività (Completate , In corso, In ritardo)
- Premi INVIO e torna al menù principale


Case 7: (Ottieni l'attività con massima priorità)

- Recupera l’attività con il maggior valore di importanza dalla coda (max-heap)
- Visualizza i dettagli di tale attività
- Premi INVIO e torna al menù principale


Case 8: (Mostra notifiche delle attività in ritardo)

- Stampa a schermo tutte le attività che risultano in ritardo
- Premi INVIO e torna al menù principale


Case 9: (Uscita dal programma)

- Visualizza un messaggio d'uscita
- Termina l'esecuzione del programma e libera la memoria allocata

