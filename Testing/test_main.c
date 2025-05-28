/* AVVISO!: Nel codice sono stati utilizzati e implementati
            comandi 'system' per ottenere una pulizia ottimale
            del terminale. Essi potrebbero creare conflitti o 
            bug di varia natura. "Eliminarli" se presenti. */


#include <stdio.h>
#include <stdlib.h>
#include "test_progetto.h"


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


void pulisci_schermo(void) {

#ifdef _WIN32
    system("cls");    //Per windows
#else
    system("clear");  //Per Mac/Linux
#endif

}



int main(void) {

    int scelta;
    
    
    //Apertura dei file di per registrare input, oracolo ed output

    fp_input = fopen("test_input.txt", "w");

    if (fp_input == NULL) {

        perror("Errore durante l'apertura di test_input.txt");

        exit(1);
    }
    fp_oracle = fopen("test_oracle.txt", "w");

    if (fp_oracle == NULL) {

        perror("Errore durante l'apertura di test_oracle.txt");
        fclose(fp_input);

        exit(1);
    }
    fp_output = fopen("test_output.txt", "w");

    if (fp_output == NULL) {

        perror("Errore durante l'apertura di test_output.txt");

        fclose(fp_input);
        fclose(fp_oracle);

        exit(1);
    }
    
    
    do {

        printf("\n===========================================\n");
        printf("              Menu' Testing \n");
        printf("===========================================\n");

        printf("1. Test (Aggiungi Attivita')\n");
        printf("2. Test (Aggiorna Progresso)\n");
        printf("3. Test (Report Settimanale)\n");
        printf("0. Esci dai Test\n");

        printf("===========================================\n");

        printf("Inserisci la tua scelta: ");
        
        if (scanf("%d", &scelta) != 1) {

            printf("Input non valido. Riprova...\n");

            while(getchar() != '\n');    //Svuota il buffer di input
            continue;
        }

        while(getchar() != '\n');        //Consuma il newline residuo

        switch(scelta) {      // Esegue il test corrispondente alla scelta dell'utente

            case 1:

                test_aggiungi_attivita();
                break;

            case 2:

                test_aggiorna_progresso();
                break;

            case 3:

                test_report_settimanale();
                break;

            case 0:

                printf("Uscita dai test...\n");
                break;

            default:

                printf("Scelta non valida. Riprova...\n");
        }
          printf("\n Premi INVIO per continuare...");

          getchar();
        
         pulisci_schermo();

    } while(scelta != 0);
    
    fflush(fp_input);
    fflush(fp_oracle);
    fflush(fp_output);

    fclose(fp_input);
    fclose(fp_oracle);
    fclose(fp_output);
    
    return 0;
}
