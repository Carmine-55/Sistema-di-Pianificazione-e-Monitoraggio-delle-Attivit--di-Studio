#ifndef FUNZIONI_FILE_H
#define FUNZIONI_FILE_H
#include "coda_priorita.h"

//Funzione di salvataggio delle attività nel file
int salvataggio_su_file(const char *nome_file, PCoda c);

//Funzione di caricamento delle attività 
int caricamento_da_file(const char *nome_file, PCoda c);

#endif