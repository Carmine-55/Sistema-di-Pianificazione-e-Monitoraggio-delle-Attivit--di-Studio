#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funzioni_file.h"

//Funzione che salva le attività nel file
int salvataggio_su_file(const char *nome_file, PCoda c) {
    FILE *fp = fopen(nome_file, "w");
    if (!fp) {
        perror("ERRORE NELL'APERTURA DEL FILE PER IL SALVATAGGIO");
        return 0;
    }

    for (int i = 1; i <= c->num_elementi; i++) {
        Attivita *a = &c->vet[i];
        fprintf(fp, "%s|%s|%s|%d|%d|%d\n",
             a->descrizione,
             a->corso,
             a->data_di_scadenza,
             a->tempo_stimato,
             a->importanza,
             a->stato);
    }

    fclose(fp);
    return 1;
}

//Funzione che carica le attività da file
int caricamento_da_file(const char *nome_file, PCoda c) {
    FILE *fp = fopen(nome_file, "r");
    if (!fp) {
                     // Il file non esiste ancora, quindi non c'è nessuna attività da caricare
        return 0;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        Attivita a;
        char *token;

        token = strtok(buffer, "|");
        if (!token)
        continue;
        strncpy(a.descrizione, token, sizeof(a.descrizione));
        a.descrizione[sizeof(a.descrizione) - 1] = '\0';

        token = strtok(NULL, "|");
        if (!token) 
        continue;
        strncpy(a.corso, token, sizeof(a.corso));
        a.corso[sizeof(a.corso) - 1] = '\0';

        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(a.data_di_scadenza, token, sizeof(a.data_di_scadenza));
        a.data_di_scadenza[sizeof(a.data_di_scadenza) - 1] = '\0';

        token = strtok(NULL, "|");
        if (!token)
        continue;
        a.tempo_stimato = atoi(token);

        token = strtok(NULL, "|");
        if (!token) 
        continue;
        a.importanza = (Priorita)atoi(token);

        token = strtok(NULL, "|");
        if (!token) 
        continue;
        a.stato = (Stato)atoi(token);

        inserisci(c, a);
    }

    fclose(fp);
    return 1;
}
