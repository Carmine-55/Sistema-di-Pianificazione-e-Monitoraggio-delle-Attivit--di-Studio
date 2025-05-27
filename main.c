/* AVVISO!: Nel codice sono stati utilizzati e implementati
            comandi 'system' per ottenere una pulizia ottimale
            del terminale. Essi potrebbero creare conflitti o 
            bug di varia natura. "Elimnarli" se presenti. */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "item.h"
#include "coda_priorita.h"
#include "funzioni_file.h"

#define NOME_FILE "attivita'.txt"


/* FUNZIONI RELATIVE AL MAIN */

/* ----------------------------------------------------------------

- Funzione: pulisci_schermo

- La funzione esegue la pulizia del terminale utilizzando un comando
  specifico per il sistema operativo in uso

- Specifica sintattica:  void pulisci_schermo(void) -> void

- Parametri: (Nessuno)

- Specifica semantica: pulisci_schermo() -> void 

- Pre-Condizioni: (Nessuna)

- Post-Condizioni:  Il terminale viene aggiornato  mostrando lo schermo pulito

- Ritorna: (Nessun valore)

- Effetti collaterali:  Produce output modificando il contenuto visivo del terminale

*/


void pulisci_schermo(){

    #ifdef _WIN32
       system("cls");   // Per Windows
    #else
       system("clear"); // Per Mac/Linux 
    #endif      
}

int main() {

    PCoda c = nuova_PC();
    
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

        getchar();          // Consuma il carattere di newline residuo

        switch (scelta) {

            case 1: {       //Aggiunta di una nuova attività

                Attivita nuova;

                if (aggiungi_attivita(&nuova)) {

                    inserisci(c, nuova);
                    salvataggio_su_file(NOME_FILE, c);

                } else {
                    printf("\nL'ATTIVITA' NON E' STATA AGGIUNTA A CAUSA DI UN ERRORE DI INPUT!\n");
                }

                break;
            }
            case 2: {         //Modifica un'attività esistente

                if (vuota_PC(c)) {

                    printf("\nNON E' PRESENTE NESSUNA ATTIVITA' DA MODIFICARE\n");

                } else {

                    int indice;

                    printf("\nINSERISCI L'INDICE DELL'ATTIVITA' DA MODIFICARE (1-%d): ", ottieni_numero_attivita(c));

                    scanf("%d", &indice);

                    getchar();

                    if (indice < 1 || indice > ottieni_numero_attivita(c)) {

                        printf("L'INDICE INSERITO NON E' VALIDO!\n");

                    } else {

                        Attivita* ptr = ottieni_attivita_puntatore(c, indice);
                        modifica_attivita(ptr);
                        salvataggio_su_file(NOME_FILE, c);
                    }
                }

                break;
            }


            case 3: {        //Elimina un'attività esistente

                elimina_attivita(c);
                salvataggio_su_file(NOME_FILE, c);
                break;
            }

            case 4: {        //Aggiorna il progresso di un'attività 

                if (vuota_PC(c)) {

                    printf("\nNON E' PRESENTE NESSUNA ATTIVITA' DA AGGIORNARE\n");

                } else {

                    int indice;

                    printf("\nINSERISCI L'INDICE DELL'ATTIVITA' DA AGGIORNARE (1-%d): ", ottieni_numero_attivita(c));
                    scanf("%d", &indice);
                    getchar();

                    if (indice < 1 || indice > ottieni_numero_attivita(c)) {

                        printf("L'INDICE INSERITO NON E' VALIDO!\n");

                    } else {

                        Attivita* ptr = ottieni_attivita_puntatore(c, indice);
                        aggiorna_progresso_attivita(ptr);
                        salvataggio_su_file(NOME_FILE, c);
                    }
                }

                break;
            }


            case 5: {        //Visualizza progresso

                mostra_progresso(c);
                break;
            }

            case 6: {        //Generazione del report settimanale

                genera_report_settimanale(c);
                break;
            }

            case 7: {        //Mostra l'attività con priorità massima

                Attivita max = ottieni_max(c);
                mostra_attivita(&max);
                break;
            }

            case 8: {        //Visualizza notifica di un'attività in ritardo

                mostra_notifiche(c);
                break;
            }

            case 9: {        //Uscita dall'applicazione

                printf("USCITA IN CORSO...\n");
                printf("PREMI INVIO PER USCIRE DALL'APP...");

                while(getchar() != '\n');
                break;
            }

            default: {        //Errore in caso di scelta non valida

                printf("LA SCELTA NON E' VALIDA!\n");
            }
        }
        
        if (scelta != 9) {

            printf("\nPREMI INVIO PER TORNARE AL MENU' PRINCIPALE...\n");
            while(getchar() != '\n');
        }
        
    } while (scelta != 9);
    
    free(c);

    return 0;
}