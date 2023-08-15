#include <stdio.h>
#include <stdlib.h>

typedef struct{
  int id;
  char* field1;
  int field2;
  float field3;  
}Record;

// questa � un prototipo di una funzione GLOBALE, quinid in structure.c dovremmo scrivere il suo corpo
// Cosa vogliamo fare? 
//      una funzione globale con il suo corpo
//      oppure creiamo un tipo associato alla funzione, cos� che possiamo inizializzare una variabile di questo tipo?

// Definizione funzione di confronto generica
typedef int (*compareFunction)(void*, void*);

// trattino basso cos� facciamo si che la struttura sia privata
struct _Structure{
  // array di generici elementi
  void** array;
  //capacit� TOTALE dell'array
  int capacity;
  //dimenzione ATTUALE dell'array
  int size;
};
// usiaamo il tipo definito invece che la struttura privata (col trattino)
typedef struct _Structure Structure;


//prototipi delle funzioni
Structure* structureNew();
Structure* structureFree(Structure* structure);

//inserisce l'oggetto nell'array della struttura
void structureInsert(Structure*, void*);
//rimuove l'oggetto nella posizone passata come argomento dalla struttura
void structureDelete(Structure*, int);
//ritorna il valore nella posizione passata come argomento
void* structureGet(Structure*, int);
//ritorna la size (dimenzione EFFETTIVA) della struttura
int structureSize(Structure* structure); // structure: nome della variabile Structure

//dichiarazioni funzioni di comparazione dei 3 campi
int compareField1(Record* rec1, Record* rec2);
int compareField2(Record* rec1, Record* rec2);
int compareField3(Record* rec1, Record* rec2);

//funzione che legge il file csv
void readFile(Structure* myStructure, char* file);





