//file.h 

typedef struct coda_P *PCoda;

//prototipi

PCoda nuova_PC(void);
int vuota_PC(PCoda c);
Attività ottieni_max(PCoda c);
int cancella_max(PCoda c);
int inserisci(PCoda c, Attività nuovaAttività);
static void scendi(PCoda c);
static void sali(PCoda c);