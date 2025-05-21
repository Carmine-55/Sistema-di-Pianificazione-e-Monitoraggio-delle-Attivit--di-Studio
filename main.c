#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "coda_priorita.h"

void pulisci_schermo(){
    #ifdef _WIN32
       system("cls");   //Utilizzato per windows
    #else
       system("clear"); //Utilizzato per Mac/Linux 
    #endif      
}

int main() {
    PCoda c = nuova_PC();
    int scelta;

    do {
        pulisci_schermo();
        printf("\n****** BENVENUTO NEL PROGRAMMA DI GESTIONE DELLE ATTIVITA' DI STUDIO ******\n");
        printf("1. AGGIUNGI ATTIVITA'\n");
        printf("2. MODIFICA ATTIVITA'\n");
        printf("3. ELIMINA ATTIVITA'\n");
        printf("4. COMPLETA ATTIVITA'\n");
        printf("5. VISUALIZZA PROGRESSO\n");
        printf("6. GENERA IL REPORT SETTIMANALE\n");
        printf("7. OTTIENI L'ATTIVITA' CON MASSIMA PRIORITA'\n");
        printf("8. ESCI DAL PROGRAMMA\n");
        printf("SCELTA: ");
        scanf("%d", &scelta);
        getchar(); // Evita problemi di input

        switch (scelta) {
            case 1: {
                     Attivita nuova;
                    if (aggiungi_attivita(&nuova)){
                       inserisci(c, nuova);
                }
                 else {
                       printf("\nL'ATTIVITA' NON E' STATA AGGIUNTA A CAUSA DI UN ERRORE IN INPUT!\n");
                 }
                break;
            }
            
            case 2: {
                if (vuota_PC(c)) {
                    printf("NON E' PRESENTE NESSUNA ATTIVITA' DA MODIFICARE\n");
                } else {
                    int indice;
                    printf("INSERISCI L'INDICE DELL'ATTIVITA' DA MODIFICARE (1-%d): ", c->num_elementi);
                    scanf("%d", &indice);
                    getchar();

                    if (indice < 1 || indice > c->num_elementi) {
                        printf("INDICE INSERITO NON VALIDO.\n");
                    } else {
                        modifica_attivita(&c->vet[indice]);
                    }
                }
                break;
            }
            case 3: 
                    elimina_attivita(c); 
                    break;
            case 4:
                    completa_un_attivita(c);
                    break;
            case 5: 
                    mostra_progresso(c);
                    getchar();
                    break;
            case 6: 
                    genera_report_settimanale(c);
                    break;
            case 7: {
                    
                    Attivita max = ottieni_max(c);
                    mostra_attivita(&max);
                    break;
            }
            case 8: 
                    printf("USCITA IN CORSO...\n");
                    printf("PREMI INVIO PER USCIRE DALL'APP...");
                    while(getchar() != '\n');  //Se premi invio chiudi l'applicazione
                    return 0;
                    break;

            default: 
                    printf("LA SCELTA NON E' VALIDA!\n");
        }
         printf("\n ADESSO PREMI INVIO PER TORNARE AL MENU' PRINCIPALE... \n");
         while(getchar() != '\n');   //Se premi invio ripulisce lo schermo e torna al menù principale

    } while (scelta != 8);

    free(c);
    return 0;
}