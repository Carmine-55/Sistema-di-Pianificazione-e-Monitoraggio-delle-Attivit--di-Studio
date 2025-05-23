#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funzioni_file.h"

// Funzione che permette di salvare le attività nel file
int salvataggio_su_file(const char *nome_file, PCoda c) {
    FILE *file = fopen(nome_file, "w");
    if (!file) {
        perror("ERRORE DURANTE L'APERTURA DEL FILE DI SALVATAGGIO!");
        return 0;
    }

    fprintf(file, "===========================================\n");
    fprintf(file, "          Elenco Attivita'\n");
    fprintf(file, "===========================================\n\n");

    for (int i = 1; i <= c->num_elementi; i++) {
        Attivita *a = &c->vet[i];

        fprintf(file, "Attività %d\n", i);
        fprintf(file, "Descrizione    : %s\n", a->descrizione);
        fprintf(file, "Corso          : %s\n", a->corso);
        fprintf(file, "Scadenza       : %s\n", a->data_di_scadenza);
        fprintf(file, "Tempo stimato  : %d ore\n", a->tempo_stimato);
        fprintf(file, "Priorita'      : %s\n",  (a->importanza == ALTA) ? "ALTA" : (a->importanza == MEDIA) ? "MEDIA" : "BASSA");
        fprintf(file, "Stato          : %s\n",   (a->stato == IN_RITARDO) ? "In Ritardo" : (a->stato == COMPLETATA) ? "Completata" : "In Corso");
        fprintf(file, "Progresso      : %d%%\n", a->progresso);
        fprintf(file, "Data Completamento : %s\n", (a->data_completamento[0] ? a->data_completamento : "Non disponibile"));

        fprintf(file, "-------------------------------------------\n\n");
    }

    fclose(file);
    return 1;
}

// Funzione che carica le attività dal file
int caricamento_da_file(const char *nome_file, PCoda c) {
    FILE *file = fopen(nome_file, "r");
    if (!file) {
        return 0;   // Il file potrebbe non esistere
    }

    char buffer[256];
    Attivita a;

    // Salta le intestazioni
    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);

    while (fgets(buffer, sizeof(buffer), file)) {

        //Ignora i separatori o le righe vuote
        if (buffer[0] == '-' || strlen(buffer) <= 1)
            continue;

        // Lettura dei campi salvati
        fgets(buffer, sizeof(buffer), file);
        strcpy(a.descrizione, buffer + 17);
        a.descrizione[strcspn(a.descrizione, "\n")] = '\0';

        fgets(buffer, sizeof(buffer), file);
        strcpy(a.corso, buffer + 17);
        a.corso[strcspn(a.corso, "\n")] = '\0';

        fgets(buffer, sizeof(buffer), file);
        strcpy(a.data_di_scadenza, buffer + 17);
        a.data_di_scadenza[strcspn(a.data_di_scadenza, "\n")] = '\0';

        fgets(buffer, sizeof(buffer), file);
        a.tempo_stimato = atoi(buffer + 17);

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
        
        // Lettura del campo "Data Completamento" dal file
        fgets(buffer, sizeof(buffer), file);
        if(strlen(buffer) > 21) {
        strcpy(a.data_completamento, buffer + 21);

        // Rimuove il newline in fondo, solo se è presente
         a.data_completamento[strcspn(a.data_completamento, "\n")] = '\0';
        } else {
        strcpy(a.data_completamento, "Non disponibile");
        }

        inserisci(c, a);
    }

    fclose(file);
    return 1;
}
