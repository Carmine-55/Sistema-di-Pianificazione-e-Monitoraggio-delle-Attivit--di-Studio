#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "coda_priorita.h"
#include "funzioni_file.h"
#include <time.h>
#define NOME_FILE "attivita'.txt"

// Funzione per pulire lo schermo
void pulisci_schermo(){
    #ifdef _WIN32
       system("cls");   // Per Windows
    #else
       system("clear"); // Per Mac/Linux 
    #endif      
}

// Funzione per mostrare le notifiche (attività in ritardo)
void mostra_notifiche(PCoda c) {

    int notificaPresente = 0;

    printf("===========================================\n");
    printf("      PROMEMORIA: ATTIVITA' IN RITARDO\n");
    printf("===========================================\n\n");

    for (int i = 1; i <= c->num_elementi; i++) {

        if (c->vet[i].stato == IN_RITARDO) {
            printf("Attivita': %s\n", c->vet[i].descrizione);
            printf("Scadenza : %s\n", c->vet[i].data_di_scadenza);
            printf("Progresso: %d%%\n", c->vet[i].progresso);
            printf("-------------------------------------------\n");

            notificaPresente = 1;
        }
    }

    if (!notificaPresente)
        printf("NESSUNA ATTIVITA' E' IN RITARDO!\n");
        printf("\nPREMI INVIO PER CONTINUARE");
        while (getchar() != '\n');
}

int main() {
    PCoda c = nuova_PC();
    
    // Prova a caricare il file; se fallisce, crea un nuovo file
    if (!caricamento_da_file(NOME_FILE, c)) {
        printf("ERRORE DURANTE IL CARICAMENTO DEI FILE!\nCREAZIONE DI UN NUOVO FILE...\n");
        salvataggio_su_file(NOME_FILE, c);
    }

    int scelta;
    do {
        pulisci_schermo();

        printf("===========================================\n");
        printf("   BENVENUTO NEL PROGRAMMA DI GESTIONE\n");
        printf("      DELLE ATTIVITA' DI STUDIO!\n");
        printf("===========================================\n\n");
        
        printf("MENU' PRINCIPALE:\n");
        printf("1. AGGIUNGI ATTIVITA'\n");
        printf("2. MODIFICA ATTIVITA'\n");
        printf("3. ELIMINA ATTIVITA'\n");
        printf("4. AGGIORNA PROGRESSO DELL'ATTIVITA'\n");
        printf("5. VISUALIZZA PROGRESSO\n");
        printf("6. GENERA REPORT SETTIMANALE\n");
        printf("7. OTTIENI L'ATTIVITA' CON MASSIMA PRIORITA'\n");
        printf("8. MOSTRA NOTIFICHE DI ATTIVITA' IN RITARDO\n");
        printf("9. ESCI DAL PROGRAMMA\n");
        printf("===========================================\n");
        printf("SCELTA: ");
        scanf("%d", &scelta);
        getchar(); // Pulisce il buffer

        switch (scelta) {
            case 1: {
                Attivita nuova;

                if (aggiungi_attivita(&nuova)) {
                    inserisci(c, nuova);
                    salvataggio_su_file(NOME_FILE, c);

                } else {
                    printf("\nL'ATTIVITA' NON E' STATA AGGIUNTA A CAUSA DI UN ERRORE DI INPUT!\n");
                }

                break;
            }
            case 2: {

                if (vuota_PC(c)) {
                    printf("\nNON E' PRESENTE NESSUNA ATTIVITA' DA MODIFICARE\n");

                } else {

                    int indice;

                    printf("\nINSERISCI L'INDICE DELL'ATTIVITA' DA MODIFICARE (1-%d): ", c->num_elementi);
                    scanf("%d", &indice);
                    getchar();

                    if (indice < 1 || indice > c->num_elementi) {
                        printf("L'INDICE INSERITO NON E' VALIDO!\n");

                    } else {
                        modifica_attivita(&c->vet[indice]);
                        salvataggio_su_file(NOME_FILE, c);
                    }
                }
                break;
            }

            case 3:

                elimina_attivita(c);
                salvataggio_su_file(NOME_FILE, c);
                break;

            case 4: {

                if (vuota_PC(c)) {
                    printf("\nNON E' PRESENTE NESSUNA ATTIVITA' DA AGGIORNARE\n");

                } else {

                    int indice;

                    printf("\nINSERISCI L'INDICE DELL'ATTIVITA' DA AGGIORNARE (1-%d): ", c->num_elementi);
                    scanf("%d", &indice);
                    getchar();

                    if (indice < 1 || indice > c->num_elementi) {
                        printf("L'INDICE INSERITO NON E' VALIDO!\n");

                    } else {
                        aggiorna_progresso_attivita(&c->vet[indice]);
                        salvataggio_su_file(NOME_FILE, c);
                    }
                }

                break;
            }
            case 5:

                mostra_progresso(c);
                break;

            case 6:

                genera_report_settimanale(c);
                break;

            case 7:

                Attivita max = ottieni_max(c);
                mostra_attivita(&max);
                break;

            case 8:

                mostra_notifiche(c);
                break;

            case 9:

                printf("USCITA IN CORSO...\n");
                printf("PREMI INVIO PER USCIRE DALL'APP...");
                while(getchar() != '\n');
                break;

            default:

                printf("LA SCELTA NON E' VALIDA!\n");
        }

        if (scelta != 9) {
            printf("\nPREMI INVIO PER TORNARE AL MENU' PRINCIPALE...\n");
            while(getchar() != '\n');
        }
        
    } while (scelta != 9);

    free(c);
    return 0;
}
